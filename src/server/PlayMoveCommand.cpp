/*
 * Eviatar Natan
 * 307851808
 */
/*
 * PlayMoveCommand.cpp
 *
 *  Created on: Dec 29, 2017
 *      Author: eviatar
 */

#include "PlayMoveCommand.h"
pthread_mutex_t games_lock_move;

void MakeMoveCommand::execute(vector<string> args, vector<Game*> &games,
		vector<pthread_t*> &thread_vector, int client) {
    string string = "Play " + args[0] + " " + args[1];
    int temp_player;
		unsigned int i;
    char message[BUFFERSIZE] = {0};
    strcpy(message, string.c_str());
    // locks the game vector to prevent changes
    pthread_mutex_lock(&games_lock_move);
    for(i = 0; i < games.size(); i++) {
        // searches for a specific  player socket.
        if(games[i]->getFirstPlayerSocket() == client) {
            temp_player = games[i]->getSecondPlayerSocket();
            // writes move to the player
            write(temp_player, message, BUFFERSIZE*sizeof(char));
            break;
        } else if(games[i]->getSecondPlayerSocket() == client) {
            temp_player = games[i]->getFirstPlayerSocket();
            // writes move to the player
            write(temp_player, message, BUFFERSIZE*sizeof(char));
            break;
        }
    }
    // unlocks the vector.
    pthread_mutex_unlock(&games_lock_move);
}

