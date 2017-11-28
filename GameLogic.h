/*
 * Eviatar Natan
 * 307851808
 */
/*
 * GameLogic.h
 *
 *  Created on: Nov 10, 2017
 *      Author: eviatar
 */

#ifndef GAMELOGIC_H_
#define GAMELOGIC_H_
#include "Board.h"
#include "Point.h"
#include <vector>
using namespace std;
/*
 * serves as an interface that will have multiple ways to be defined.
 * (specific game logics). the methods in this class are implemented
 * by classes that realizes the interface.
 */
class GameLogic {
public:
  /*
   * not used, as it is an interface and cannot be instantiated.
   */
  GameLogic();
  /*
   * checks the available moves on the board for the current player.
   * receives the current player's and other player symbols (X/O),
   * and references to a vector of points (that will be filled) in
   * case there are possible moves, and the current state of the board.
   */
  virtual void availableMoves(vector<Point>& points,Board*& board,
      char& symbol,char& othersymbol)=0;
  /*
   * flips discs of the opposite player.
   * receives the current player's and other player symbols (X/O)
   * references to a point (the chosen move)
   * and the current state of the board.
   * returns a counter which represents the amount of discs
   * that has been flipped.
   */
  virtual int flipDiscs(Board*& board,Point &refPoint,
      char&symbol,char &othersymbol)=0;
  /*
   * receive a reference to a vector of points and sorts it,
   * first by X values, and second by Y values.
   */
  virtual void sortPoints(vector<Point>&ref)=0;
  /*
   * receives a reference to a vector of points and removes
   * duplicates.
   */
  virtual void removeDuplicatePoints(vector<Point>&ref)=0;
  /*
   * uses the default destructor.
   */
  virtual ~GameLogic();
};
#endif /* GAMELOGIC_H_ */
