/*
 * Eviatar Natan
 * 307851808
 */
/*
 * gameListCommand.h
 *
 *  Created on: Dec 28, 2017
 *      Author: eviatar
 */

#ifndef GAMELISTCOMMAND_H_
#define GAMELISTCOMMAND_H_
#include "Command.h"

#define NOGAMES "no available games\n"
#define NOGAMESIZE 19

/*
 * responsible for sending to a client a list of
 * games that he can join.
 */
class GetGameListCommand : public Command {
public:
	/*
	 * executes the command.
	 */
  void execute(vector<string> args, vector<Game*> &games,
  		vector<pthread_t*> &thread_vector, int client = 0);
};

#endif /* GAMELISTCOMMAND_H_ */
