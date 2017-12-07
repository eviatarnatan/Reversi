/*
 * RemoteGame.cpp
 *
 *  Created on: Dec 6, 2017
 *      Author: eviatar
 */

#include "RemoteGame.h"
#include "iostream"
#include "stdlib.h"
using namespace std;
RemoteGame::RemoteGame(GameLogic *logic, Player *player, int board_size) {
	// TODO Auto-generated constructor stub
	logic_ = logic;
	int row_size = board_size, column_size = board_size;
	gameboard_ = new Board(row_size, column_size);
	player_ = player;
}
void RemoteGame::play() {
	try {
		((RemotePlayer*)player_)->connectToServer();
	} catch (const char *msg) {
		cout << "failed to connect to server. Reason: " << msg << endl;
		exit(-1);
	}
	cout << "success connecting to server";
}
void RemoteGame::end() {

}
RemoteGame::~RemoteGame() {
	// TODO Auto-generated destructor stub
	delete logic_;
	delete gameboard_;
	delete player_;
}

