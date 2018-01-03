/*
 * Eviatar Natan
 * 307851808
 */
/*
 * Handler.cpp
 *
 *  Created on: Jan 1, 2018
 *      Author: eviatar
 */

#include "Handler.h"

// creating mutexes
pthread_mutex_t lock_games_handler_run;
pthread_mutex_t lock_games_handler_close_threads;
pthread_mutex_t lock_games_handler_client;
pthread_mutex_t lock_games_handler_game;
pthread_mutex_t lock_games_handler_delete_games;
pthread_mutex_t lock_games_handler_delete_thread;

void Handler::run(int clientSocket) {
    int n;
    pthread_t thread;
    HandleArgs *handle_args = new HandleArgs();
    pthread_mutex_lock(&lock_games_handler_run);
    handle_args->games = &games_;
    pthread_mutex_unlock(&lock_games_handler_run);
    pthread_mutex_lock(&lock_games_handler_run);
    handle_args->threadVector = &threadVector;
    pthread_mutex_unlock(&lock_games_handler_run);
    handle_args->game = NULL;
    handle_args->socket = clientSocket;
    try {
        n = pthread_create(&thread, NULL, handlePlayer, (void*)handle_args);
    } catch (const char* msg) {
        throw msg;
    }
    if (n) {
        cout << "Error: unable to create a thread" << endl;
        exit(-1);
    }
}

void Handler::closeThreads() {
    // locks game's vector
    pthread_mutex_lock(&lock_games_handler_close_threads);
    int size = games_.size();
    for(int i = size - 1; i >= 0; i--) {
        int first = games_[i]->getFirstPlayerSocket();
        int second = games_[i]->getSecondPlayerSocket();
        if(second == 0) {
            write(first, CLOSE, CLOSESIZE * sizeof(char));

        } else {
            //sends close to both players
            write(first, CLOSE, CLOSESIZE * sizeof(char));
            write(second, CLOSE, CLOSESIZE * sizeof(char));
        }
    }
    // unlock game's vector
    pthread_mutex_unlock(&lock_games_handler_close_threads);
    // locks the games vector to prevent changes.
    pthread_mutex_lock(&lock_games_handler_close_threads);
    size = threadVector.size();
    for(int i = size - 1; i >= 0; i--) {
        threadVector.pop_back();
    }
    // unlock the vector.
    pthread_mutex_unlock(&lock_games_handler_close_threads);
}

void* Handler::handlePlayer(void* handleArgs) {
    CommandsManager commands_manager;
    CommandWithArgs command_with_args;
    char buffer[BUFFERSIZE] = {0};
    HandleArgs *handle_args1 = (HandleArgs*)handleArgs;
    // locks the vector of games to prevent changes.
    pthread_mutex_lock(&lock_games_handler_client);
    vector<Game*>& temp = *handle_args1->games;
    // unlocks the vector.
    pthread_mutex_unlock(&lock_games_handler_client);
    pthread_mutex_lock(&lock_games_handler_client);
    vector<pthread_t*> &thread_temp = *handle_args1->threadVector;
    pthread_mutex_unlock(&lock_games_handler_client);
    // reading the command from the player
    int n = read(handle_args1->socket, buffer, BUFFERSIZE*sizeof(char));
    if (n == -1) {
        cout << "Error reading from socket" << endl;
        return NULL;
    }
    if (n == 0) {
        cout << "client disconnected" << endl;
        return NULL;
    }
    // converting the command.
    command_with_args = analyzeData(buffer);
    try {
        commands_manager.executeCommand(command_with_args.command,
        		command_with_args.args, temp, thread_temp, handle_args1->socket);
    } catch (const char* msg) {
        throw msg;
    }
}

void* Handler::handleGame(void* handleArgs) {
    CommandsManager commands_manager;
    CommandWithArgs command_with_args;
    HandleArgs *handle_args1 = (HandleArgs*)handleArgs;
    int n, temp;
    int player_num = FIRST, first_player, second_player;
    char buffer[BUFFERSIZE] = {0};
    // locks the vector of games.
    pthread_mutex_lock(&lock_games_handler_game);
    vector<Game*> &tempGames = *handle_args1->games;
    // unlocks the vector.
    pthread_mutex_unlock(&lock_games_handler_game);
    pthread_mutex_lock(&lock_games_handler_game);
    vector<pthread_t*> &threadTemp = *handle_args1->threadVector;
    // unlocks the vector.
    pthread_mutex_unlock(&lock_games_handler_game);
    pthread_mutex_lock(&lock_games_handler_game);
    Game *currentGame = handle_args1->game;
    // unlocks the vector.
    pthread_mutex_unlock(&lock_games_handler_game);
    // locks the the current game.
    pthread_mutex_lock(&lock_games_handler_game);
    first_player = currentGame->getFirstPlayerSocket();
    // unlocks the game.
    pthread_mutex_unlock(&lock_games_handler_game);
    // locks the current game.
    pthread_mutex_lock(&lock_games_handler_game);
    second_player = currentGame->getSecondPlayerSocket();
    // unlocks the game.
    pthread_mutex_unlock(&lock_games_handler_game);
    // writing the position number to the first player.
    n = write(first_player, &player_num, sizeof(int));
    if (n == -1) {
        cout << "Error writing to a socket" << endl;
        return NULL;
    }
    // writing the position number to the second player.
    player_num = SECOND;
    n = write(second_player, &player_num, sizeof(int));
    if (n == -1) {
        cout << "Error writing to a socket" << endl;
        return NULL;
    }
    if (second_player == -1)
        throw "Error on accept";
    int current_client = first_player;
    int waiting_client = second_player;
    do {
        //read the info sent from the client.
        int n = read(current_client, buffer, BUFFERSIZE*sizeof(char));
        if (n == -1) {
            return NULL;
        }
        if (n == 0) {
            cout << "client disconnected" << endl;
            return NULL;
        }
        // extracting the command from the buffer.
        command_with_args = analyzeData(buffer);
        // we will exectue the command as long as it's not "End" or "NoMoves".
        if(command_with_args.command.compare("End ") != 0 && command_with_args.command.compare("NoMoves") != 0) {
            try {
                // executes the command
                commands_manager.executeCommand(command_with_args.command, command_with_args.args,
                                  tempGames, threadTemp, current_client);
            } catch (const char *msg) {
            	cout << "catch inside" << endl;
                throw msg;
            }
            if (command_with_args.command.compare("close") == 0) {
            	break;
            }
        }
        // switch between the players.
        temp = current_client;
        current_client = waiting_client;
        waiting_client = temp;
    // end ing the game if the command is either "End" or "close".
    } while(strcmp(command_with_args.command.c_str(), "End") != 0
            && strcmp(command_with_args.command.c_str(), "close") != 0);
    // locks the vector of games.
    pthread_mutex_lock(&lock_games_handler_game);
    deleteGame(*handle_args1->games, handle_args1->game->getName());
    // unlocks the vector.
    pthread_mutex_unlock(&lock_games_handler_game);
    // locks the vector of threads.
    pthread_mutex_lock(&lock_games_handler_game);
    deleteThread(*handle_args1->threadVector, handle_args1->game->getThread());
    // unlocks the vector.
    pthread_mutex_unlock(&lock_games_handler_game);

    close(first_player);
    close(second_player);
    pthread_exit(NULL);
}

CommandWithArgs Handler::analyzeData(char* buffer) {
    int i,j, args = 0;
    string start_message = STARTMESSAGE, command, arguments[FOUR];
    CommandWithArgs command_with_args;
    for(i = 0; i < BUFFERSIZE; i++) {
        if(buffer[i] != '\0') {
            if(buffer[i] != ' ') {
                // seperating the command from the string.
                command.append(sizeof(char) ,buffer[i]);
            } else {
                break;
            }
        } else {
            break;
        }
    }
    if(buffer[i] != '\0') {
        i++;
    }
    for(j = i; j < BUFFERSIZE; j++) {
        if(buffer[j] != '\0') {
            // seperating the arguments.
            if(buffer[j] != ' ') {
                arguments[args].append(sizeof(char), buffer[j]);
            } else {
                args += 1;
            }
        } else {
            break;
        }
    }
    command_with_args.command = command;
    // inserting the arguments to a vector of strings.
    for(int j = 0; j <= args; j++) {
        if(arguments[j].compare("") != 0) {
            command_with_args.args.push_back(arguments[j]);
        }
    }
    return command_with_args;
}

void Handler::deleteGame(vector<Game*> &games, string game_Name) {
    int i;
    // locks the vector of games to prevent changes.
    pthread_mutex_lock(&lock_games_handler_delete_games);
    int size = games.size();
    for (i = 0; i < size; i++) {
        //game will be deleted if the names are equal.
        if (games.at(i)->getName().compare(game_Name) == 0) {
            games.erase(games.begin() + i);
        }
    }
    // unlocks the vector.
    pthread_mutex_unlock(&lock_games_handler_delete_games);
}

void Handler::deleteThread(vector<pthread_t *> &threads, pthread_t pthread) {
    int i;
    // locks the vector of threads to prevent changes.
    pthread_mutex_lock(&lock_games_handler_delete_thread);
    int size = threads.size();
    for (i = 0; i < size; i++) {
        // will delete if threads are equal
        if (*threads.at(i) == pthread) {
            threads.erase(threads.begin() + i);
        }
    }
    // unlocks the vector.
    pthread_mutex_unlock(&lock_games_handler_delete_thread);
}

void Handler::printThreadAndGamesVectorSize() {
    cout << "threads: ";
    //pthread_mutex_lock(&gamesLockHander);
    cout << threadVector.size() << endl;
    //pthread_mutex_unlock(&gamesLockHander);
    cout << "games: ";
    //pthread_mutex_lock(&gamesLockHander);
    cout << games_.size() << endl;
    //pthread_mutex_unlock(&gamesLockHander);
}
