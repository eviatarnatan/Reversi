/*
 * Eviatar Natan
 * 307851808
 */
/*
 * Game.cpp
 *
 *  Created on: Jan 1, 2018
 *      Author: eviatar
 */

#include "Game.h"

Game::Game(string game_name, int socket1, int socket2) {
    name = game_name;
    first_player_socket_ = socket1;
    second_player_socket_ = socket2;
    status_ = false;
    thread_ = 0;
}

string Game::getName() {
    return name;
}

bool Game::getGameStatus() {
    return status_;
}

int Game::getFirstPlayerSocket() {
    return first_player_socket_;
}

int Game::getSecondPlayerSocket() {
    return second_player_socket_;
}

pthread_t Game::getThread() {
    return thread_;
}

void Game::joinGame(int new_player) {
    second_player_socket_ = new_player;
    status_ = true;
}

void Game::setThread(pthread_t new_game_thread) {
    thread_ = new_game_thread;
}

