/*
 * Eviatar Natan
 * 307851808
 */
/*
 * Game.cpp
 *
 *  Created on: Nov 10, 2017
 *      Author: eviatar
 */

#include "Game.h"
Game::Game() {
  // TODO Auto-generated constructor stub
  logic_ = new ReversiLogic();
  int row_size = 8,column_size = 8;
  gameboard_ = new Board(row_size,column_size);
  playerX_=new HumanPlayer('X','O');
  initialize();

}
void Game::initialize(){
	cout << "Welcome to Reversi!" << endl;
	cout << "Please choose if you would like to play against another player " <<
			"or against the computer" << endl;
	cout << "1) Play against another player" << endl;
	cout << "2) Play against the computer" << endl;
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
		if (game_choice == 1) {
			cout << "You've chosen a game against another player" << endl;
			playerO_ = new HumanPlayer('O','X');
			break;
		} else if (game_choice == 2) {
			cout <<"You've chosen a game against the computer" << endl;
			playerO_ = new AiPlayer('O','X');
			break;
		} else {
			cout << "Invalid choice. Please choose a valid choice." << endl;
		}
	} while (game_choice != 1 || game_choice != 2);
}
void Game::play() {
  bool no_moves = false;
  playerX_->setMyTurn(true);
  Player *&refX = playerX_;
  Player *&refO = playerO_;
  gameboard_->print();
  //if true, each player takes his turn, breaks if both can't move.
  while (playerX_->getMyTurn() == true || playerO_->getMyTurn() == true) {
    //gameboard_->print();
    //checks if it's X player turn.
    if (playerX_->getMyTurn() == true) {
      playerX_->turn(logic_, gameboard_, refO);
      if (playerX_->getMyTurn() == false) {
        if (playerX_->getMyTurn() == false && playerO_->getMyTurn() == false
            && no_moves == true)
          break;
        playerO_->setMyTurn(true);
        no_moves = true;
        continue;
      }
      playerX_->setMyTurn(false);
      playerO_->setMyTurn(true);
      no_moves = false;
    }
    //else it's O player turn.
    else {
      playerO_->turn(logic_, gameboard_, refX);
      if (playerO_->getMyTurn() == false) {
        if (playerO_->getMyTurn() == false && playerX_->getMyTurn() == false
            && no_moves == true)
          break;
        playerX_->setMyTurn(true);
        no_moves = true;
        continue;
      }
      playerO_->setMyTurn(false);
      playerX_->setMyTurn(true);
      no_moves = false;
    }
    //checks if the board is full, if it is, will break the loop.
    if (playerX_->getDisksNum() + playerO_->getDisksNum()
        == gameboard_->getRowSize() * gameboard_->getColumnSize()) {
      gameboard_->print();
      break;
    }
  }
}
void Game::end() {
  if (playerX_->getDisksNum() > playerO_->getDisksNum()) {
    cout << "Player X Won";
  }
  else if (playerX_->getDisksNum() < playerO_->getDisksNum()) {
    cout << "Player O Won";
  }
  else {
    cout << "It's a draw";
  }

}
Game::~Game() {
  // TODO Auto-generated destructor stub
  delete gameboard_;
  delete logic_;
  delete playerX_;
  delete playerO_;
}

