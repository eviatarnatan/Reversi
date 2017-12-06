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

#include "LocalGame.h"
LocalGame::LocalGame(GameLogic *logic, Player *player1, Player *player2, int board_size) {
  // TODO Auto-generated constructor stub
  logic_ = logic;
  int row_size = board_size,column_size = board_size;
  gameboard_ = new Board(row_size,column_size);
  playerX_ = player1;
  playerO_ = player2;

}
void LocalGame::play() {
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
void LocalGame::end() {
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
LocalGame::~LocalGame() {
  // TODO Auto-generated destructor stub
  delete gameboard_;
  delete logic_;
  delete playerX_;
  delete playerO_;
}

