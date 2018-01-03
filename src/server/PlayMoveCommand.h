/*
 * Eviatar Natan
 * 307851808
 */
/*
 * PlayMoveCommand.h
 *
 *  Created on: Dec 29, 2017
 *      Author: eviatar
 */

#ifndef PLAYMOVECOMMAND_H_
#define PLAYMOVECOMMAND_H_

#include "Command.h"
#include <cstring>
#define BUFFERSIZE 200

/*
 * sends a move to the other player.
 */
class MakeMoveCommand : public Command {
public:
	/*
	 * executes the command
	 */
	void execute(vector<string> args, vector<Game*> &games,
			vector<pthread_t*> &thread_vector, int client = 0);
};

#endif /* PLAYMOVECOMMAND_H_ */
