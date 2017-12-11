/*
 * Eviatar Natan
 * 307851808
 */
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
RemoteGame::RemoteGame(GameLogic *logic, RemotePlayer *player,
		int board_size) {
	// TODO Auto-generated constructor stub
	logic_ = logic;
	int row_size = board_size, column_size = board_size;
	gameboard_ = new Board(row_size, column_size);
	player_ = player;
	//tries to connect the player to the server.
	try {
		player_->connectToServer();
	} catch (const char *msg) {
		cout << "failed to connect to server. Reason: " << msg << endl;
		exit(-1);
	}
	cout << "success connecting to server" << endl;
}
void RemoteGame::play() {
	//prints the board at the beginning of the game.
	bool first_turn = true;
	Point end_game(0,0);
	gameboard_->print();
	if (player_->getSymbol() == 'O') {
		cout << "waiting for other's player move..." << endl;
	}
	vector<Point> moves;
	vector<Point> moves_ref;
	while (true) {
		if (player_->getSymbol() == 'X' && first_turn == true) {
			first_turn = false;
			Point move(-1,-1);
			move=player_->RemoteTurn(logic_, gameboard_);
			cout << "Waiting for other's player move" << endl;
			player_->sendPoint(move);
		}
		//not the first turn
		else {
			Point move(-1,-1);;
			move = player_->receivePoint();
			//checks if both player turns were skipped, in order to end the game.
			if (move.getPointX() == -2 && move.getPointY() == -2) {
				end_game.setPointX(0);
				end_game.setPointY(0);
				break;
			}
			bool opponent_no_move = false;
			char symbol = player_->getSymbol();
			char other_symbol = player_->getOppositeSymbol();
			char &symbol_ref = symbol;
			char &other_symbol_ref = other_symbol;
			Point &move_ref = move;
			// if last moved was skipped
			if (move.getPointX() == -1 && move.getPointY() == -1) {
				gameboard_->print();
				cout << other_symbol << "turn was skipped because he had no moves"
						<< endl;
				opponent_no_move = true;
			} else {
				//updates the board with the opponent's last move
				logic_->flipDiscs(gameboard_,move_ref,other_symbol_ref,symbol_ref);
				gameboard_->print();
				cout << other_symbol << " played (" << move.getPointX() << ","
						<< move.getPointY() << ")" << endl << endl;
			}
			move = player_->RemoteTurn(logic_, gameboard_);
			//if current player has no available moves after previous player turn.
			if (move.getPointX() == -1 && move.getPointY() == -1
					&& opponent_no_move == true) {
				end_game.setPointX(-2);
				end_game.setPointY(-2);
				break;
			}
			cout << "Waiting for other's player move..." << endl;
			player_->sendPoint(move);
		}
	}
	player_->sendPoint(end_game);
}
void RemoteGame::end() {
	int black_discs = 0, white_discs = 0;
	char **gameboard_array = gameboard_->getBoardTable();
	for (int i = 0; i < gameboard_->getRowSize(); i++) {
		for (int j = 0; j < gameboard_->getColumnSize(); j++) {
			if (gameboard_array[i][j] == 'X') {
				black_discs++;
			}
			if (gameboard_array[i][j] == 'O') {
				white_discs++;
			}
		}
	}
	if (black_discs > white_discs) {
			cout << "Player 1 won" << endl;
	} else if (black_discs < white_discs) {
			cout << "Player 2 won" << endl;
	} else {
			cout << "It's a draw" << endl;
	}
}
RemoteGame::~RemoteGame() {
	// TODO Auto-generated destructor stub
	delete logic_;
	delete gameboard_;
	delete player_;
}

