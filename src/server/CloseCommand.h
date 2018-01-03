/*
 * Eviatar Natan
 * 307851808
 */
/*
 * CloseCommand.h
 *
 *  Created on: Dec 29, 2017
 *      Author: eviatar
 */

#ifndef CLOSECOMMAND_H_
#define CLOSECOMMAND_H_
#include "Command.h"
#include <cstring>

#define CLOSE "close"
#define CLOSESIZE 8

/*
 * responsible for closing a game.
 */
class CloseGameCommand : public Command {
public:
	/*
	 * executes the command to close a game
	 */
	void execute(vector<string> args, vector<Game*> &game,
			vector<pthread_t*> &thread_vector, int client = 0);
};


#endif /* CLOSECOMMAND_H_ */
