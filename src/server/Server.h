/*
 * Eviatar Natan
 * 307851808
 */
/*
 * Server.h
 *
 *  Created on: Dec 5, 2017
 *      Author: eviatar
 */

#ifndef SERVER_H_
#define SERVER_H_
#include "CommandsManager.h"
#include "Game.h"
#include "Handler.h"
#include <string.h>
#include <cstdlib>
#include <pthread.h>
#define MAX_CONNECTED_CLIENTS 10
#define STARTMESSAGE "Start"
#define BUFFERSIZE 200
#define FIRST 1
#define SECOND 2

/*
 * holds info sent to static functions in handler
 */
typedef struct AcceptStruct {
    Handler *handler;
    int *running;
    int *client_socket;
    int *server_socket;
}AcceptStruct;

/*
 * holds info for waitForCloseMessage function.
 */
typedef struct Info {
    Handler *handler;
    int *running;
}Info;

class Server {
public:
	/*
	 * the server constructor.
	 */
	Server(int port);
	/*
	 * start running the server. the server each time wait for two clients to
	 * log to the server. after the clients finished playing the game. the server
	 * will wait for the next 2 players to join the game.
	 */
	void start();
	/*
	 * stops the server socket
	 */
	void stop();
	/*
	 * receives a struct with client and accepts new client
	 */
  static void *acceptNewClient(void* acceptStruct);
  /*
   * wait for close message, and then closes all threads, games and the server.
   */
static void *waitForCloseMessage(void* handler);
	/*
	 * the destructor
	 */
	virtual ~Server();
private:
	int port_;
	int server_socket_;
	int running;
};

#endif /* SERVER_H_ */
