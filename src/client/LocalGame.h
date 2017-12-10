/*
 * Eviatar Natan
 * 307851808
 */
/*
 * Game.h
 *
 *  Created on: Nov 10, 2017
 *      Author: eviatar
 */

#ifndef LOCALGAME_H_
#define LOCALGAME_H_
#include "Board.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "AiPlayer.h"
#include "GameLogic.h"
#include "ReversiLogic.h"
#include "Game.h"
#include <iostream>
/*
 * The main class of the game.
 * it's responsible for creating the game's players, logic, and board,
 * which are classes that serves as his data members.
 * the class serves as the flow of the game (initialize a new game, play turns,
 * and end the game).
 */
class LocalGame: public Game {
public:
  /*
   * constructor - creates a new specific gamelogic and a dynamic board.
   */
  LocalGame(GameLogic *logic, Player *player1, Player *player2, int board_size);
  /*
   * the gameflow. each time one player plays it's turn. after each turn,
   * the turn passes to the other player. when there are no available moves
   * for both of the players or the board is full, the "play" phase will end.
   */
  void play();
  /*
   * checks which player has the most discs and announces it at the winner.
   * in case of a draw, an appropriate message will be shown.
   */
  void end();
  /*
   * destructor - deletes the dynamic allocated logic, game board and players.
   */
  virtual ~LocalGame();
private:
  Board* gameboard_;
  GameLogic* logic_;
  Player* playerX_;
  Player* playerO_;
};

#endif /* LOCALGAME_H_ */
