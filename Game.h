/*
 * Game.h
 *
 *  Created on: Dec 6, 2017
 *      Author: eviatar
 */

#ifndef GAME_H_
#define GAME_H_

class Game {
public:
	Game();
  /*
   * the gameflow. each time one player plays it's turn. after each turn,
   * the turn passes to the other player. when there are no available moves
   * for both of the players or the board is full, the "play" phase will end.
   */
  virtual void play() = 0;
  /*
   * checks which player has the most discs and announces it at the winner.
   * in case of a draw, an appropriate message will be shown.
   */
  virtual void end() = 0;
  //virtual ~Game();
  virtual ~Game();
};

#endif /* GAME_H_ */
