/*
 * Eviatar Natan
 * 307851808
 */
/*
 * CommandsManager.cpp
 *
 *  Created on: Dec 28, 2017
 *      Author: eviatar
 */

#include "CommandsManager.h"

CommandsManager::CommandsManager() {
	commands_map_["start"] = new StartCommand();
	commands_map_["list_games"] = new GetGameListCommand();
	commands_map_["join"] = new joinGameCommand();
	commands_map_["play"] = new MakeMoveCommand();
	commands_map_["close"] = new CloseGameCommand();
}

CommandsManager::~CommandsManager() {
	// creates an iterator to go over the map
	map<string, Command *>::iterator it;
	for (it = commands_map_.begin(); it != commands_map_.end(); it++) {
			// deletes the map
			delete it->second;
	}
}

void CommandsManager::executeCommand(string command, vector<string> args,
		vector<Game*> &games,vector<pthread_t*> &thread_vector, int client) {
	// creates the command based on given command
	Command *commandObj = commands_map_[command];
	try {
			// executes the command
			commandObj->execute(args, games, thread_vector, client);
	} catch (const char* msg) {
			throw msg;
	}
}
