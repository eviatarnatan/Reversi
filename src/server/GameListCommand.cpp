/*
 * Eviatar Natan
 * 307851808
 */
/*
 * gameListCommand.cpp
 *
 *  Created on: Dec 28, 2017
 *      Author: eviatar
 */

#include "GameListCommand.h"

pthread_mutex_t gamesLockList;

void GetGameListCommand::execute(vector<string> args, vector<Game*> &games,
		vector<pthread_t*> &thread_vector,int client) {
    int n, list_size = 0;
    string list = "";
    const char* send;
    // locking the vector of the games to prevent changes
    pthread_mutex_lock(&gamesLockList);
    for(unsigned int i = 0; i < games.size(); i++) {
        if(games[i]->getGameStatus() == 0) {
            // appends games that haven't started yet to the list
            list.append(games[i]->getName());
            // appends end line after each game name
            list.append("\n");
        }
    }
    pthread_mutex_unlock(&gamesLockList);

    list_size = list.size();
    // sends the list's sized
    n = write(client, &list_size, sizeof(int));
    if (n == -1) {
        throw "Error writing the command to the socket";
    }
    if (n == 0) {
        throw "Error, connection lost...";
    }
    // sends the list as string
    if(list_size != 0) {
        send = list.c_str();
        // sends the list.
        n = write(client, send, list_size * sizeof(char));
    } else {
        // if the list is empty
        n = write(client, &NOGAMES, NOGAMESIZE * sizeof(char));
    }
    if (n == -1) {
        throw "Error writing the command to the socket";
    }
    if (n == 0) {
        throw "Error, connection lost...";
    }
}

