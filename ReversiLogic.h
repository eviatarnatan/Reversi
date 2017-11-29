/*
 * Eviatar Natan
 * 307851808
 */
/*
 * ReversiLogic.h
 *
 *  Created on: Nov 10, 2017
 *      Author: eviatar
 */

#ifndef REVERSILOGIC_H_
#define REVERSILOGIC_H_
#include "GameLogic.h"
/*
 * the default logic of Reversi.
 * it implements the "Interface" GameLogic.
 */
class ReversiLogic: public GameLogic {
public:
  /*
   * the default constructor.
   */
  ReversiLogic();
   /* checks the available moves on the board for the current player.
   * receives the current player's and other player symbols (X/O),
   * and references to a vector of points (that will be filled) in
   * case there are possible moves, and the current state of the board.
   */
  void availableMoves(vector<Point>& points,Board*& board,
      char& symbol,char& other_symbol);
  /*
   * flips discs of the opposite player.
   * receives the current player's and other player symbols (X/O)
   * references to a point (the chosen move)
   * and the current state of the board.
   * returns a counter which represents the amount of discs
   * that has been flipped.
   */
  virtual int flipDiscs(Board*& board,Point &ref_point,char&symbol,
      char& other_symbol);
  /* same as availableMoves, but specific for vertical moves.
  */
  void verticalMoves(Board*& board,vector<Point> &moves,
      char& current,char& standby);
  /* same as availableMoves, but specific for horizontal moves.
  */
  void horizontalMoves(Board*& board,vector<Point> &moves,
      char& current,char& standby);
  /* same as availableMoves, but specific for top diagonal moves.
  */
  void topDiagonalMoves(Board*& board,vector<Point> &moves,
      char& current,char& standby);
  /* same as availableMoves, but specific for bottom diagonal moves.
  */
  void bottomDiagonalMoves(Board*& board,vector<Point> &moves,
      char& current,char& standby);
  /*
   * receive a reference to a vector of points and sorts it,
   * first by X values, and second by Y values.
   */
  void sortPoints(vector<Point>& ref);
  /*
   * receives a reference to a vector of points and removes
   * duplicates.
   */
  void removeDuplicatePoints(vector<Point>& ref);
  /*
   * flips discs up and down from the player's chosen point.
   * and counts them.
   */
  void verticalFlip(Board*& board,int& counter,Point& ref_point,
      char& symbol,char &other_symbol);
  /*
   * flips discs left and right from the player's chosen point.
   * and counts them.
   */
  void horizontalFlip(Board*& board,int& counter,Point& ref_point,
      char& symbol,char &other_symbol);
  /*
   * flips discs top left and top right from the player's chosen point.
   * and counts them.
   */
  void topDiagonalFlip(Board*& board, int& counter, Point& ref_point,
      char& symbol, char &other_symbol);
  /*
   * flips discs bottom left and bottom right from the player's chosen point.
   * and counts them.
   */
  void bottomDiagonalFlip(Board*& board, int& counter, Point& ref_point,
      char& symbol, char& other_symbol);
  /*
   * default destructor.
   */
  virtual ~ReversiLogic();
};

#endif /* REVERSILOGIC_H_ */
