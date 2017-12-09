/*
 * Eviatar Natan
 * 307851808
 */
/*
 * AiPlayer.h
 *
 *  Created on: Nov 24, 2017
 *      Author: eviatar
 */

#ifndef AIPLAYER_H_
#define AIPLAYER_H_
#include "Player.h"
/*
 * the class inherits from Player class. responsible of the AI player.
 */
class AiPlayer: public Player {
public:
	/*
	 * creates a new Ai player with a given symbol and opposite symbol.
	 */
	AiPlayer(char symbol, char other_symbol);
  /*
   * returns the current amount of discs the player has.
   */
  virtual int getDisksNum();
  /*
   * adds new amount of discs to the amount the player has.
   */
  virtual void setDisksNum(int disks_num);
  /*
   * gets the player's turn status.
   */
  virtual bool getMyTurn();
  /*
   * sets the player's turn status.
   */
  virtual void setMyTurn(bool status);
  /*
   * returns the symbol (O/X) of the player.
   */
  virtual char getSymbol();
  /*
   * sets the symbol (O/X) of the player.
   */
  virtual void setSymbol(char symbol);
  /*
   * returns the symbol (O/X) of the opposite player.
   */
  virtual char getOppositeSymbol();
  /*
   * sets the symbol (O/X) of the opposite player.
   */
  virtual void setOppositeSymbol(char other_symbol);
  /*
   * the Ai's turn. if there are available moves, the Ai chooses the
   * move based on the minimax strategy. if there aren't any possible moves,
   * the turn will pass to the other player.
   */
  void turn(GameLogic*& logic, Board*& board, Player*& other);
  /*
   * uses the default destructor.
   */
	virtual ~AiPlayer();
private:
  int disks_num_;
  bool my_turn_;
  char symbol_;
  char other_symbol_;
};

#endif /* AIPLAYER_H_ */
