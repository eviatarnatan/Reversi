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
void RemotePlayer::getPlayingOrderSymbol() {
	int get_player_order;
	int wait_for_player;
	int player_order;
	player_order =read(client_socket_,&get_player_order, sizeof(get_player_order));
	if (player_order == -1) {
		cout << "Error reading player order from socket" << endl;
	}
	else {
		if (get_player_order == 1) {
			//wait for other player to join before making the first move
			player_order = read(client_socket_,&wait_for_player,sizeof(wait_for_player));
			if (player_order == -1) {
				cout << "error reading from socket" << endl;
			}
			cout << "Order: 1 - You play black ('X')" << endl;
		}
		else {
			cout << "Order: 2 - You play white ('O')" << endl;
			this->setSymbol('O');
			this->setOppositeSymbol('X');
		}
	}
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
	   Point no_move(-1,-1);
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
	 //set counter with the current amount of flips occured this turn.
	 logic->flipDiscs(board,ref_point,symbol,other_symbol);
	 board->print();
	 return point;
}
void RemotePlayer::sendPoint(Point move) {
	int x_value = move.getPointX();
	int y_value = move.getPointY();
	//sending x value to server
	int n = write(client_socket_, &x_value,sizeof(x_value));
	if (n == -1) {
		throw "error writing to socket";
	}
	//sending y value to server
	n = write(client_socket_, &y_value, sizeof(y_value));
	if (n == -1) {
		throw "error writing to socket";
	}
}
Point RemotePlayer::receivePoint() {
	int x_value, y_value;
	int n = read(client_socket_, &x_value, sizeof(x_value));
	if (n == -1) {
		throw "error reading from socket";
	}
	n = read(client_socket_, &y_value, sizeof(y_value));
	if (n == -1) {
		throw "error reading from socket";
	}
	Point recent_move(x_value,y_value);
	return recent_move;
}
RemotePlayer::~RemotePlayer() {
	// TODO Auto-generated destructor stub
}

