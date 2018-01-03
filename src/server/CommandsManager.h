/*
 * Eviatar Natan
 * 307851808
 */
/*
 * CommandsManager.h
 *
 *  Created on: Dec 28, 2017
 *      Author: eviatar
 */

#ifndef COMMANDSMANAGER_H_
#define COMMANDSMANAGER_H_
#include <vector>
#include <map>
#include "iostream"
#include "Command.h"
#include "StartCommand.h"
#include "PlayMoveCommand.h"
#include "JoinCommand.h"
#include "GameListCommand.h"
#include "CloseCommand.h"
using namespace std;

/*
 * the class holds a map of available commands between the player
 * and the server.
 */
class CommandsManager {
public:
	/*
	 * the constructor. adds the commands to the map.
	 */
	CommandsManager();
	/*
   * the destructor.
	 */
	~CommandsManager();
	/*
   * executes a command based on the given command string.
	 */
	void executeCommand(string command, vector <string> args, vector<Game*> &games,
			vector<pthread_t*> &threadVector,int client = 0);
private:
    map<string, Command *> commands_map_;
};
#endif /* COMMANDSMANAGER_H_ */
