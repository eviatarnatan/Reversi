/*
 * Eviatar Natan
 * 307851808
 */
/*
 * Game.h
 *
 *  Created on: Jan 1, 2018
 *      Author: eviatar
 */

#ifndef GAME_H_
#define GAME_H_

#include <sys/socket.h>
#include <string>

using namespace std;

class Game {
public:
	/*
   * the constructor.
	 */
	Game(string game_name, int socket1, int socket2);
	/*
   * returns the game's name
	 */
	string getName();
	/*
   * returns the game's status.
   * true for a game that begun, false if waiting for 2nd player to join.
	 */
	bool getGameStatus();
	/*
   * returns the first player socket.
	 */
	int getFirstPlayerSocket();
	/*
   * returns the second player socket.
	 */
	int getSecondPlayerSocket();
	/*
   * return's the game's thread.
	 */
	pthread_t getThread();
	/*
	 * sets the second player socket, and change status to true,
	 * in order to be able to begin the game.
	 */
	void joinGame(int new_player);
	/*
   * sets the thread for the game
	*/
	void setThread(pthread_t new_game_thread);
private:
	string name;
	int first_player_socket_;
	int second_player_socket_;
	bool status_;
	pthread_t thread_;
};


#endif /* GAME_H_ */
