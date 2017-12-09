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
	RemoteGame(GameLogic *logic, RemotePlayer *player, int board_size);
	void checkRemotePlayerConnection();
	void play();
	void end();
	virtual ~RemoteGame();
private:
  Board* gameboard_;
  GameLogic* logic_;
  RemotePlayer* player_;
};

#endif /* REMOTEGAME_H_ */
