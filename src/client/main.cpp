/*
 * Eviatar Natan
 * 307851808
 */
/*
 * main.cpp
 *
 *  Created on: Oct 22, 2017
 *      Author: eviatar
 */

#include <iostream>
#include <fstream>
#include <string.h>
#include "LocalGame.h"
#include "RemoteGame.h"
string getIPFromFile();
int getPortFromFile();
int main () {

	cout << "Welcome to Reversi!" << endl;
	cout << "Please choose if you would like to play against another player " <<
			"or against the computer" << endl;
	cout << "1) Play against another player" << endl;
	cout << "2) Play against the computer" << endl;
	cout << "3) Play against a remote player" << endl;
	GameLogic *logic = new ReversiLogic();
	int board_size = 4;
	Game *game;
	int game_choice;
	do {
		cin >> game_choice;
		if (!cin.fail()) {
			//skip bad input if the first number in string is 1 or 2.
			cin.ignore(256, '\n');
		} else {
			cin.clear();
			cin.ignore(256, '\n');
		}
		//local game vs human
		if (game_choice == 1) {
				cout << "You've chosen a game against another player" << endl;
				Player *player = new HumanPlayer('X','O');
				Player *player2 = new HumanPlayer('O','X');
				game = new LocalGame(logic, player, player2, board_size);
				break;
		//local game vs Ai
		} else if (game_choice == 2) {
				cout <<"You've chosen a game against the computer" << endl;
				Player *player = new HumanPlayer('X','O');
				Player *player2 = new AiPlayer('O','X');
				game = new LocalGame(logic, player, player2, board_size);
				break;
		//remote game vs remote player
		} else if (game_choice == 3) {
				string ip = getIPFromFile();
				int port = getPortFromFile();
				RemotePlayer *player = new RemotePlayer(ip.c_str(), port, 'X', 'O');
				game = new RemoteGame(logic, player, board_size);
				player->getPlayingOrderSymbol();
				break;
		} else {
			cout << "Invalid choice. Please choose a valid choice." << endl;
		}
	} while (game_choice != 1 || game_choice != 2 || game_choice != 3);
  game->play();
  game->end();
  delete game;
  return 0;

}
/*
 * the function tries to open the client settings file.
 * if the opening was successful, the function will read the ip
 * number that is written in the file and return the string with the
 * ip number. otherwise, will return the string "failed".
 */
string getIPFromFile(){
	ifstream client_settings;
	string IP;
	client_settings.open("ClientSettings.txt");
	if (client_settings.is_open()) {
		string ip_string;
		client_settings >> ip_string;
		client_settings >> IP;
		client_settings.close();
		cout << "ip is: " << IP << endl;
		return IP;
	}
	else {
		cout << "failed opening the file" << endl;
		string s = "failed";
		return s;
	}
}
/*
 * the function tries to open the client settings file.
 * if the opening was successful, the function will read the port
 * number that is written in the file and return the string with the
 * port number. if opening failed, will return the port -1;
 */
int getPortFromFile() {
	ifstream client_settings;
	int port;
	client_settings.open("ClientSettings.txt");
	//checks if file opening was successful
	if (client_settings.is_open()) {
		string ip_string, ip_number_string,port_string;
		client_settings >> ip_string;
		client_settings >> ip_number_string;
		client_settings >> port_string;
		client_settings >> port;
		client_settings.close();
		cout << "port is " << port << endl;
		return port;
	}
	else {
		cout << "failed opening the file" << endl;
		port = -1;
		return port;
	}
}


