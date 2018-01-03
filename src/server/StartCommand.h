/*
 * Eviatar Natan
 * 307851808
 */
/*
 * startCommand.h
 *
 *  Created on: Dec 28, 2017
 *      Author: eviatar
 */

#ifndef STARTCOMMAND_H_
#define STARTCOMMAND_H_
#include "Command.h"

#define EXISTS "AlreadyExist"
#define EXISTSIZE 15
#define DOSENTEXIST "DosentExist"
#define DOSENTEXISTSIZE 13

/*
 * creates a new game and add it to the list
 */
class StartCommand : public Command {
public:
	/*
	 * executes the command.
	 */
	void execute(vector<string> args, vector<Game*> &games,
			vector<pthread_t*> &thread_vector, int client = 0);
};
#endif /* STARTCOMMAND_H_ */
