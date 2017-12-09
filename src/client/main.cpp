/*
 * Eviatar Natan
 * 307851808
 */
/*
 * main.cpp
 *
 *  Created on: Oct 22, 2017
 *      Author: eviatar
 */

#include <iostream>

#include "LocalGame.h"
#include "RemoteGame.h"
int main () {

	Printer printer;
	printer.welcomeMessage();
	GameLogic *logic = new ReversiLogic();
	int board_size = 4;
	Game *game;
	int game_choice;
	do {
		cin >> game_choice;
		if (!cin.fail()) {
			//skip bad input if the first number in string is 1 or 2.
			cin.ignore(256, '\n');
		} else {
			cin.clear();
			cin.ignore(256, '\n');
		}
		if (game_choice == 1) {
				cout << "You've chosen a game against another player" << endl;
				Player *player = new HumanPlayer('X','O');
				Player *player2 = new HumanPlayer('O','X');
				game = new LocalGame(logic, player, player2, board_size);
				break;
		} else if (game_choice == 2) {
				cout <<"You've chosen a game against the computer" << endl;
				Player *player = new HumanPlayer('X','O');
				Player *player2 = new AiPlayer('O','X');
				game = new LocalGame(logic, player, player2, board_size);
				break;
		} else if (game_choice == 3) {
				//first logged player is assumed to be the X player.
				RemotePlayer *player = new RemotePlayer("127.0.0.1", 8000, 'X', 'O');
				game = new RemoteGame(logic, player, board_size);
				player->getPlayingOrderSymbol();
				break;
		} else {
			cout << "Invalid choice. Please choose a valid choice." << endl;
		}
	} while (game_choice != 1 || game_choice != 2 || game_choice != 3);
  game->play();
  game->end();
  delete game;
  return 0;

}



