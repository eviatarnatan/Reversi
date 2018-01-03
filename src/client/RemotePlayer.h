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
#define BUFFERSIZE 200
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
   * the player will wait for the server to write a playing number.
   * if it's 1, the player will play as black 'X'.
   * if it's 2, the player will play as white 'O'.
   * if the write result is different from 1 or 2, we'll throw it.
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
   * will be (0,0), otherwise a vaild point on the board will be returned.
   */
  Point RemoteTurn(GameLogic*& logic, Board*& board);
  /*
   * receives a point which is the last played move of the current player, and
   * writes it back to the server.
   */
  void sendPoint(Point move);
  /*
   * reads a message from the server. the message is then analyzed and then
   * converts to a point that is returned, which represents the move the other
   * player has played. will convert to 0,0 or -3,-3 in case of nomoves/close.
   */
  Point receivePoint();
  /*
   * the "lobby".
   * a menu will be printed to the player, from which he can start a new game,
   * print the list of available games that he can join, or join a game, based
   * on his choice (1 start, 2 game_list, 3 join).
   */
  void mainMenuPlayerChoice();
  /*
   * analyze the info received from the server, in order to be able to return
   * a point to the player that reads the data.
   */
  Point analyzeData(char* buffer);
  /*
   * disconnect the player from the game, and then reconnects him.
   */
  void reconnect();
  /*
   * disconnects the player from the game (without reconnecting him).
   */
  void closeConnection();
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
