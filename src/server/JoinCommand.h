/*
 * Eviatar Natan
 * 307851808
 */
/*
 * JoinCommand.h
 *
 *  Created on: Dec 28, 2017
 *      Author: eviatar
 */

#ifndef JOINCOMMAND_H_
#define JOINCOMMAND_H_
#include "Command.h"
#include "Handler.h"
#define STARTMESSAGE "Start"
#define STARTMESSAGESIZE 10
#define NOTEXIST "NotExist"
#define NOTEXISTSIZE 10
#define FIRST 1
#define SECOND 2

/*
 * adds a second player to a game that haven't started yet,
 * and then starts it.
 */
class joinGameCommand : public Command {
public:
		/*
		 * executes the command.
		 */
    void execute(vector<string> args, vector<Game*> &games,
    		vector<pthread_t*> &thread_vector, int client = 0);
};

#endif /* JOINCOMMAND_H_ */
