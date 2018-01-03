/*
 * Eviatar Natan
 * 307851808
 */
/*
 * RemoteGame.h
 *
 *  Created on: Dec 6, 2017
 *      Author: eviatar
 */

#ifndef REMOTEGAME_H_
#define REMOTEGAME_H_
#include "RemotePlayer.h"
#include "Game.h"
class RemoteGame : public Game {
public:
	/*
	 * the constructor - receives the game logic, the remote player, and the
	 * board size (the size of row and column)
	 */
	RemoteGame(GameLogic *logic, RemotePlayer *player, int board_size);
	/*
	 *the remote game flow. responsible for making moves on the board based on
	 *the points it receives. if the point (0,0) was received, it means
	 *that the last turn was skipped.if the point (-3,-3) was received, it means:
	 *1. that both players turns have been skipped in a row, which then stops the
	 *game.
	 *2. the server has been closed.
	 *in both cases, the player's sockets will be closed, and we will return back
	 *from this function to the main class.
	 */
	void play();
	/*
	 * checks the board after the game is over. the function accumulates the
	 * amount of black player cells ('X') and white player cells ('O') and then
	 * announce the winner based on the amount (unless black and white cells are
	 * equal, which means the game has ended in a draw, and then the function
	 * will announce the the game has ended in a draw).
	 */
	void end();
	// the destructor. delete the dynamic allocated logic, gameboard, and player.
	virtual ~RemoteGame();
private:
  Board* gameboard_;
  GameLogic* logic_;
  RemotePlayer* player_;
};

#endif /* REMOTEGAME_H_ */
