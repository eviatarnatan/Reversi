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
  int getDisksNum();
  /*
   * adds new amount of discs to the amount the player has.
   */
  void setDisksNum(int disks_num);
  /*
   * gets the player's turn status.
   */
  bool getMyTurn();
  /*
   * sets the player's turn status.
   */
  void setMyTurn(bool status);
  /*
   * returns the symbol (O/X) of the player.
   */
  char getSymbol();
  /*
   * sets the symbol (O/X) of the player.
   */
  void setSymbol(char symbol);
  /*
   * returns the symbol (O/X) of the opposite player.
   */
  char getOppositeSymbol();
  /*
   * sets the symbol (O/X) of the opposite player.
   */
  void setOppositeSymbol(char other_symbol);
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
