/*
 * Eviatar Natan
 * 307851808
 */
/*
 * startCommand.cpp
 *
 *  Created on: Dec 28, 2017
 *      Author: eviatar
 */

#include "StartCommand.h"

// creating mutexes
pthread_mutex_t start_game_lock;

void StartCommand::execute(vector<string> args, vector<Game*> &games, vector<pthread_t*> &threadVector, int client) {
    Game* new_game = NULL;
    // locks game's vector to prevent changes
    pthread_mutex_lock(&start_game_lock);
    for(int i = 0; i < games.size(); i++) {
        // checking if the game exists.
        if(games[i]->getName().compare(args[0]) == 0) {
            new_game = games[i];
        }
    }
    // unlock the vector.
    pthread_mutex_unlock(&start_game_lock);
    if(new_game != NULL) {
        // in case the game already exists.
        write(client, &EXISTS, EXISTSIZE * sizeof(char));
        return;
    }
    // create a new game if it does not exist.
    write(client, &DOSENTEXIST, DOSENTEXISTSIZE * sizeof(char));
    new_game = new Game(args[0], client, 0);
    // locks game's vector to prevent changes.
    pthread_mutex_lock(&start_game_lock);
    games.push_back(new_game);
    // unlocks the vector.
    pthread_mutex_unlock(&start_game_lock);
}

