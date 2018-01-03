/*
 * Eviatar Natan
 * 307851808
 */
/*
 * CloseCommand.cpp
 *
 *  Created on: Dec 29, 2017
 *      Author: eviatar
 */

#include "CloseCommand.h"

pthread_mutex_t lockClose;

void CloseGameCommand::execute(vector<string> args, vector<Game*> &games,
                               vector<pthread_t*> &thread_vector, int client) {
	unsigned int i, temp_player;
	// locks the vector of games
	pthread_mutex_lock(&lockClose);
	for(i = 0; i < games.size(); i++) {
		// searching player's socket
		if (games[i]->getFirstPlayerSocket() == client) {
				temp_player = games[i]->getSecondPlayerSocket();
				// sending "close" message to the second player
				write(temp_player, &CLOSE, CLOSESIZE * sizeof(char));
				break;
		// in case the socket we search for belongs the second player
		} else if (games[i]->getSecondPlayerSocket() == client) {
				temp_player = games[i]->getFirstPlayerSocket();
				// sending "close" message to the first player
				write(temp_player, &CLOSE, CLOSESIZE * sizeof(char));
				break;
		}
	}
	// unlocks the vector of games
	pthread_mutex_unlock(&lockClose);
}
