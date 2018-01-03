/*
 * Eviatar Natan
 * 307851808
 */
/*
 * Command.h
 *
 *  Created on: Dec 27, 2017
 *      Author: eviatar
 */

#ifndef COMMAND_H_
#define COMMAND_H_

#include <vector>
#include "iostream"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "Game.h"

using namespace std;

/*
 * command interface.
 */
class Command {
public:
    /*
	   * receives a string of arguments, vectors of games running on the server
	   * and threads running, and a player's socket
     */
    virtual void execute(vector<string> args, vector<Game*> &games,
                         vector<pthread_t*> &threadVector, int client = 0) = 0;
    /*
	  * default destructor
    */
    virtual ~Command() {}
};

#endif /* COMMAND_H_ */
