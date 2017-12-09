/*
 * RemotePlayer.h
 *
 *  Created on: Dec 5, 2017
 *      Author: eviatar
 */

#ifndef REMOTEPLAYER_H_
#define REMOTEPLAYER_H_
#include "Player.h"
class RemotePlayer : public Player{
public:
	RemotePlayer(const char *serverIP, int serverPort, char Symbol, char other_symbol);
	void connectToServer();
  /*
   * returns the current amount of discs the player has.
   */
	void getPlayingOrderSymbol();
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
   * the player's turn. on each turn, the player will see the available moves
   * that he can make, and choose his desired move. the board will be updated
   * after his choice, and the number of discs he and the opposite player have
   * will be updated. in case there are no available moves, the turn will pass
   * to the other player.
   */
  virtual void turn(GameLogic*& logic, Board*& board, Player*& other);
  Point RemoteTurn(GameLogic*& logic, Board*& board);
  void sendPoint(Point move);
  Point receivePoint();
	virtual ~RemotePlayer();
private:
	const char *server_IP_;
	int server_port_;
	int client_socket_;
  int disks_num_;
  bool my_turn_;
	char symbol_;
	char other_symbol_;
};

#endif /* REMOTEPLAYER_H_ */
