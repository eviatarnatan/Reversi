/*
 * Eviatar Natan
 * 307851808
 */
/*
 * Handler.h
 *
 *  Created on: Jan 1, 2018
 *      Author: eviatar
 */

#ifndef HANDLER_H_
#define HANDLER_H_
#include "CommandsManager.h"
#include "Game.h"
#include <vector>
#include <string.h>
#include <cstdlib>

#define FIRST 1
#define SECOND 2
#define FOUR 4
#define BUFFERSIZE 200

typedef struct CommandWithArgs {
    string command;
    vector<string> args;
}CommandWithArgs;

typedef struct HandleArgs {
    int socket;
    Game* game;
    vector<Game*> *games;
    vector<pthread_t*> *threadVector;
}HandleArgs;

/*
 * Handles the games and clients.
 */
class Handler {
public:
	/*
	 * starts running the thread
	 */
	void run(int clientSocket);
	/*
	 * close the threads in order to close the server.
	 */
	void closeThreads();
	/*
	 * reads commands from the user and executes them.
	 */
	static void *handlePlayer(void* socket);
	/*
	 * reads commands from the user and executes them.
	 */
	static void *handleGame(void* gameToHandle);
private:
	vector<Game*> games_;
	vector<pthread_t*> threadVector;
	/*
	 * prints the size of the vectores of games and threads.
	 */
	void printThreadAndGamesVectorSize();
	/*
	 * analyze the received data and extracts it.
	 */
	static CommandWithArgs analyzeData(char* buffer);
	/*
	 * deletes a game from the vector of games
	 */
	static void deleteGame(vector<Game*> &games, string gameName);
	/*
	 * deletes a thread from the list of threads
	*/
	static void deleteThread(vector<pthread_t*> &threads, pthread_t pthread);
};
#endif /* HANDLER_H_ */
