/*
 * Eviatar Natan
 * 307851808
 */
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
	/*
	 * the constructor - receives the client's ip server, the port, and symbols
	 * to determine if the player is 'X' or 'O' and sets them.
	 * the second player to connect to the server will become
	 * the white 'O' player.
	 */
	RemotePlayer(const char *serverIP, int serverPort, char Symbol, char other_symbol);
	/*
	 * responsible for connecting the player to the server. checks for possible
	 * errors while trying to connect to the server. if all tests has passed,
	 * the player will be connected to the server.
	 */
	void connectToServer();
  /*
   * based on the order the two clients have logged on, this function will
   * determine which player will be black and which will be white. after both
   * players has been connected to the server, both of them will receive
   * a number (1 or 2) which will determine their playing order and color.
   */
	void getPlayingOrderSymbol();
	/*
	 * returns the number of disks the player has.
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
   * not used.
   */
  virtual void turn(GameLogic*& logic, Board*& board, Player*& other);
  /*
   * the player's turn. on each turn, the player will see the available moves
   * that he can make, and choose his desired move. the board will be updated
   * after his choice in case there are no available moves, the returned point
   * will be (-1,-1), otherwise a vaild point on the board will be returned.
   */
  Point RemoteTurn(GameLogic*& logic, Board*& board);
  /*
   * receives a point which is the last played move of the current player, and
   * writes it back to the server.
   */
  void sendPoint(Point move);
  /*
   * reads a point from the server and writes it back to the current player.
   */
  Point receivePoint();
  /*
   * default destructor
   */
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
