/*
 * Eviatar Natan
 * 307851808
 */
/*
 * RemotePlayer.cpp
 *
 *  Created on: Dec 5, 2017
 *      Author: eviatar
 */

#include "RemotePlayer.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
using namespace std;
RemotePlayer::RemotePlayer(const char *serverIP, int serverPort, char symbol,
		char other_symbol):
	server_IP_(serverIP), server_port_(serverPort), client_socket_(0) {
	disks_num_ = 2;
	my_turn_ = false;
	symbol_ = symbol;
	other_symbol_ = other_symbol;
}

void RemotePlayer::connectToServer() {
	// create a socket point
	client_socket_ = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket_ == -1) {
		throw "Error opening socket";
	}
	// convert the ip string to a network address
	struct in_addr address;
	if (!inet_aton(server_IP_, &address)) {
		throw "Cant parse IP address";
	}
	// get a hostent structure for the given host address
	struct hostent *server;
	server = gethostbyaddr((const void *)&address, sizeof address, AF_INET);
	if (server == NULL) {
		throw "Host is unreachable";
	}
	//create a structure for the server address
	struct sockaddr_in server_address;
	bzero((char*)&address, sizeof(address));

	server_address.sin_family = AF_INET;
	memcpy((char*)&server_address.sin_addr.s_addr, (char *)server->h_addr, server->h_length);
	// htons converts values between host and network byte orders
	server_address.sin_port = htons(server_port_);
	// establish a connection with the TCP server
	if (connect(client_socket_, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
		throw "Error connecting to server";
	}
	cout << "Connected to server" << endl;
	cout << "Waiting for other player to join..." << endl;
}
int RemotePlayer::getDisksNum() {
  return disks_num_;
}
void RemotePlayer::setDisksNum(int disks_num) {
  disks_num_ = disks_num_ + disks_num;
}
bool RemotePlayer::getMyTurn() {
  return my_turn_;
}
void RemotePlayer::setMyTurn(bool status) {
  my_turn_ = status;
}
char RemotePlayer::getSymbol() {
  return symbol_;
}
void RemotePlayer::setSymbol(char symbol) {
  symbol_ = symbol;
}
char RemotePlayer::getOppositeSymbol() {
  return other_symbol_;
}
void RemotePlayer::setOppositeSymbol(char other_symbol) {
  other_symbol_ = other_symbol;
}
void RemotePlayer::turn(GameLogic*& logic, Board*& board, Player*& other) {

}
void RemotePlayer::getPlayingOrderSymbol() {
	int player_order;
	char buffer[BUFFERSIZE];
	//reading playing number from server
	player_order = read(client_socket_,buffer,BUFFERSIZE*sizeof(char));
	if (player_order == -1) {
		throw "Error reading player order from socket";
	}
	if(strcmp(buffer, "close") == 0) {
	        throw "Game closed";
	}
	player_order = buffer[0];
	if (player_order == 1) {
		cout << "you play black 'X'" << endl;
	}
	if(player_order == 2) {
		cout << "you play white 'O'" << endl;
	  setSymbol('O');
	  setOppositeSymbol('X');
	}
}
Point RemotePlayer::RemoteTurn(GameLogic*& logic, Board*& board){
	 int row, column;
	 vector<Point> possible_moves;
	 vector<Point>& moves_ref = possible_moves;
	 char &symbol = symbol_;
	 char &other_symbol = other_symbol_;
	 cout << symbol_ << ": It's your move." << endl;
	 logic->availableMoves(moves_ref, board, symbol, other_symbol);
	 if (possible_moves.empty() == false) {
	   logic->sortPoints(moves_ref);
	   logic->removeDuplicatePoints(moves_ref);
	   cout << "Your possible moves: ";
	   //print available moves
	   for (unsigned int i = 0; i < possible_moves.size(); i++) {
	     if (i > 0) {
	       cout << ",";
	     }
	     cout << "(" << possible_moves.at(i).getPointX() << "," <<
	         possible_moves.at(i).getPointY() << ")";
	   }
	   cout << endl << endl;
	 }
	 //in case there are no avaiable moves.
	 else{
	   cout << "no possible moves. play passes back to the other player." << endl;
	   setMyTurn(false);
	   Point no_move(0,0);
	   return no_move;
	 }
	 bool legal = false;
	 cout << "Please enter your move row col:";
	 while (true) {
	   while (true) {
	     cin >> row >> column;
	     if (!cin.fail()) {
	       //skip bad input
	       cin.ignore(256, '\n');
	       break;
	   } else{
	       // user didn't input a number/bad number and char combo
	       cout << "Please enter numbers only." << endl;
	       cin.clear();
	       cin.ignore(256, '\n');
	     }
	   }
	   for (unsigned int i = 0; i < possible_moves.size(); i++) {
	     if (possible_moves.at(i).getPointX() == row) {
	       if (possible_moves.at(i).getPointY() == column ) {
	         legal = true;
	       }
	     }
	   }
	   if (legal == true)
	       break;
	   cout << "illegal move. choose another:";
	 }
	 Point point(row,column);
	 Point &ref_point = point;
	 logic->flipDiscs(board,ref_point,symbol,other_symbol);
	 board->print();
	 return point;
}
void RemotePlayer::sendPoint(Point move) {
	string play = "play ";
	int x_value = move.getPointX();
	int y_value = move.getPointY();
	char message[BUFFERSIZE] = {0};
	if(x_value == -3 && y_value == -3) {
			play = "close";
			cout << play << endl;
	} else {
			char num;
			//converting values by ascii
			num = (char) (x_value + 48);
			play = play + num + " ";
			num = (char) (y_value + 48);
			play = play + num;
			cout << play << endl;
	  }
	strcpy(message, play.c_str());
	int n = write(client_socket_, message, BUFFERSIZE*sizeof(char));
	if (n == -1) {
		if (x_value == -3 && y_value == -3) {
			throw "game closed";
		}
		throw "error writing to socket";
	}
	if (n == 0) {
		if (x_value == -3 && y_value == -3) {
			throw "game closed";
		}
		throw "error, opponent disconnected...";
	}
}
Point RemotePlayer::receivePoint() {
	int n;
	Point recent_move(-4, -4);
	char buffer[BUFFERSIZE] = {0};
	do {
		n = read(client_socket_, buffer, BUFFERSIZE*sizeof(char));
		if (n == -1) {
			throw "error reading from socket";
		}
		if (n == 0) {
			throw "game closed";
		}
		if (strcmp(buffer, "close") == 0) {
			recent_move.setPointX(-3);
			recent_move.setPointY(-3);
			close(client_socket_);
			return recent_move;
		}
		recent_move = analyzeData(buffer);
	} while ((recent_move.getPointX() < 0 || recent_move.getPointY() < 0) &&
			(recent_move.getPointX() != -2 && recent_move.getPointY() != -2));
	return recent_move;
}

void RemotePlayer::mainMenuPlayerChoice() {
	string command, name = "";
	char msg[BUFFERSIZE] = {0};
  char receive[BUFFERSIZE] = {0};
  char list[BUFFERSIZE] = {0};
	int player_choice, n, size_of_list;
	bool flag = false;
	while (!flag) {
		cout << "Welcome to our server! in order to play, please choose one"
				<<" of the following options:" << endl;
		cout << "1) Start a new game: type start <name>" << endl;
		cout << "2) Get the list of games: type list_games" << endl;
		cout << "3) Join a game: type join <name>" << endl;
		//cin >> player_choice;
	   while (true) {
	     cin >> player_choice;
	     if (!cin.fail()) {
	       //skip bad input
	       cin.ignore(50, '\n');
	       break;
	   } else{
	       // user didn't input a number/bad number and char combo
	       cout << "Please enter numbers only." << endl;
	       cin.clear();
	       cin.ignore(256, '\n');
	       continue;
	     }
	   }
		if (player_choice != 1 && player_choice != 2 && player_choice != 3) {
			cout << "invalid choice, please choose a valid choice" << endl;
			continue;
		}
		if (player_choice == 1 || player_choice == 3) {
			//enter the name of the game
			cin >> name;
		}
		if (player_choice == 1) {
				command = "start " + name;
		} else if (player_choice == 2) {
				command = "list_games";
		} else if (player_choice == 3) {
				command = "join " + name;
		} else {
				command = "invalidOption";
		}
		strcpy(msg, command.c_str());
		cout << msg << endl;
		n = write(client_socket_, msg, BUFFERSIZE * sizeof(char));
		if (n == -1) {
			throw "failed to write command to server";
		}
		if (n == 0) {
			throw "connection error";
		}
		if (player_choice == 1 || player_choice == 3) {
			do {
				//reads the answer from the server
				n = read(client_socket_, receive, BUFFERSIZE * sizeof(char));
				if (n == -1) {
					throw "error reading answer from server";
				}
				if (n == 0) {
					throw "connection error";
				}
			} while (strcmp(receive,"") == 0);
		}
		if (command == "list_games") {
			n = read(client_socket_, &size_of_list, sizeof(size_of_list));
			if (n == -1) {
				throw "error reading list's size from server";
			}
			if (n == 0) {
				throw "connection error";
			}
			n = read(client_socket_, list, BUFFERSIZE * sizeof(char));
			if (n == -1) {
				throw "error reading game list from server";
			}
			if (n == 0) {
				throw "connection error";
			}
			if (size_of_list== 0) {
					cout << "there are currently no games on the server" << endl;
					cout << "you can create a new one by entering: '1 ' + 'game_name'" << endl;
					reconnect();
					continue;
		  } else {
					cout << "list of games that you can join:" << endl;
					for (int i = 0; i < size_of_list; i++) {
						cout << list[i];
					}
					cout << endl;
					reconnect();
					continue;
			}
		}
		//if player tried to join a non exist game, or create one that exists:
		else if (strcmp(receive, "NotExist") == 0) {
			cout << "you can't join the game because it does not exists or it's full already" << endl;
			cout << "however, you can create a game with that name" << endl;
			reconnect();
			continue;
		}
		else if (strcmp(receive, "AlreadyExist") == 0) {
			cout << "you can't create a game with that name because it's already exists" << endl;
			reconnect();
			continue;
		}
		//player choice was successful, ready to play
		flag = true;
	}
	if (player_choice == 1) {
		cout << "waiting for another player to join..." << endl;
	}
	try {
		getPlayingOrderSymbol();
	} catch (const char* msg) {
		cout << msg << endl;
		throw msg;
	}
}
Point RemotePlayer::analyzeData(char* buffer) {
		int x,y;
    const int num = 2;
    int i,j, args = 0;
    string command, arguments[num];
    for(i=0; i < BUFFERSIZE; i++) {
        if(buffer[i] != '\0') {
            if(buffer[i] != ' ') {
                command.append(sizeof(char) ,buffer[i]);
            } else {
                break;
            }
        } else {
            break;
        }
    }
    if(buffer[i] != '\0') {
        i++;
    }
    for(j=i; j < BUFFERSIZE; j++) {
        if(buffer[j] != '\0') {
            if(buffer[j] != ' ') {
                arguments[args].append(sizeof(char), buffer[j]);
            } else {
                args += 1;
            }
        } else {
            break;
        }
    }
    if(args == 1 && arguments[1].compare("") != 0) {
       x = atoi(arguments[0].c_str());
       y = atoi(arguments[1].c_str());
    }
    Point parsed(x,y);
    return parsed;
}

void RemotePlayer::reconnect() {
    close(client_socket_);
    client_socket_ = 0;
    try {
        connectToServer();
    } catch (const char* msg) {
        throw msg;
    }
}
void RemotePlayer::closeConnection() {
	close(client_socket_);
}
RemotePlayer::~RemotePlayer() {
	// TODO Auto-generated destructor stub
}

