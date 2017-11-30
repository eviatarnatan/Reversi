/*
 * Eviatar Natan
 * 307851808
 */
/*
 * Player.h
 *
 *  Created on: Nov 3, 2017
 *      Author: eviatar
 */

#ifndef PLAYER_H_
#define PLAYER_H_
#include "GameLogic.h"
#include "Board.h"
/*
 * declares a player that participates in the game.
 * serves as an interface which is inherited and defined by
 * HumanPlayer and AiPlayer classes.
 */
class Player {
public:
  /*
   * the constructor - sets the starting number of discs of the player,
   * and sets his turn to false (not his turn). sets his and the other player
   * symbols (X/O) to space ' ', which will be defined on "turn" function.
   * note: This class serves as an interface. the above is true for the
   * inherited classes, HumanPlayer and AiPlayer.
   */
  Player();
  /*
   * returns the current amount of discs the player has.
   */
  virtual int getDisksNum() = 0;
  /*
   * adds new amount of discs to the amount the player has.
   */
  virtual void setDisksNum(int disks_num) = 0;
  /*
   * gets the player's turn status.
   */
  virtual bool getMyTurn() = 0;
  /*
   * sets the player's turn status.
   */
  virtual void setMyTurn(bool status) = 0;
  /*
   * returns the symbol (O/X) of the player.
   */
  virtual char getSymbol() = 0;
  /*
   * sets the symbol (O/X) of the player.
   */
  virtual void setSymbol(char symbol) = 0;
  /*
   * returns the symbol (O/X) of the opposite player.
   */
  virtual char getOppositeSymbol() = 0;
  /*
   * sets the symbol (O/X) of the opposite player.
   */
  virtual void setOppositeSymbol(char other_symbol) = 0;
  /*
   * the player's turn. on each turn, the player will see the available moves
   * that he can make, and choose his desired move. the board will be updated
   * after his choice, and the number of discs he and the opposite player have
   * will be updated. in case there are no available moves, the turn will pass
   * to the other player.
   */
  virtual void turn(GameLogic*& logic, Board*& board, Player*& other) = 0;
  /*
   * uses the default destructor.
   */
  virtual ~Player();
};

#endif /* PLAYER_H_ */
