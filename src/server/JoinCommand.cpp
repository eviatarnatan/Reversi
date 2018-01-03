/*
 * Eviatar Natan
 * 307851808
 */
/*
 * JoinCommand.cpp
 *
 *  Created on: Dec 28, 2017
 *      Author: eviatar
 */

#include "JoinCommand.h"

pthread_mutex_t lock_join;

void joinGameCommand::execute(vector<string> args, vector<Game*> &games,
		vector<pthread_t*> &thread_vector, int client) {
	unsigned int i, n;
	int second_player;
	Game* joined = NULL;
	// lock to prevent changes.
	pthread_mutex_lock(&lock_join);
	for(i = 0; i < games.size(); i++) {
		// joining the game if the name is correct and it haven't begun yet.
		if(games[i]->getGameStatus() == 0 && games[i]->getName() == args[0]) {
				games[i]->joinGame(client);
				joined = games[i];
				break;
		}
	}
	// unlock the vector.
	pthread_mutex_unlock(&lock_join);
	if(joined != NULL) {
		pthread_t thread;
		// locks the game to prevent changes.
		pthread_mutex_lock(&lock_join);
		second_player = joined->getSecondPlayerSocket();
		// unlocks the game.
		pthread_mutex_unlock(&lock_join);
		// writing start message to the second player.
		write(second_player, &STARTMESSAGE, STARTMESSAGESIZE*sizeof(char));

		HandleArgs *handleArgs = new HandleArgs();
		// locks the game's vector to prevent changes.
		pthread_mutex_lock(&lock_join);
		handleArgs->games = &games;
		// unlocks the vector.
		pthread_mutex_unlock(&lock_join);
		pthread_mutex_lock(&lock_join);
		handleArgs->threadVector = &thread_vector;
		pthread_mutex_unlock(&lock_join);
		pthread_mutex_lock(&lock_join);
		handleArgs->game = joined;
		// unlocks the game.
		pthread_mutex_unlock(&lock_join);
		handleArgs->socket = client;
		try {
				n = pthread_create(&thread, NULL, Handler::handleGame, (void*)handleArgs);
				// locks the game to prevent changes.
				pthread_mutex_lock(&lock_join);
				handleArgs->game->setThread(thread);
				// unlocks the vector.
				pthread_mutex_unlock(&lock_join);
				// locks the threads vector to prevent changes.
				pthread_mutex_lock(&lock_join);
				// inserts the thread to the list
				thread_vector.push_back(&thread);
				// unlocks the vector.
				pthread_mutex_unlock(&lock_join);
		} catch (const char* msg) {
				throw msg;
		}
		if (n) {
				cout << "Error: unable to create a thread" << endl;
				exit(-1);
		}
	} else {
		// in case the game doesn't exist we sent a proper message.
		write(client, &NOTEXIST, NOTEXISTSIZE*sizeof(char));
	}
}
