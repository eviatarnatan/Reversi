/*
 * Eviatar Natan
 * 307851808
 */
/*
 * Board.h
 *
 *  Created on: Oct 22, 2017
 *      Author: eviatar
 */

#ifndef BOARD_H_
#define BOARD_H_
/*
 * The class creates a new game board, which can be printed.
 */
class Board {
public:
  /*
   * Creates a new game board with a given row and column parameter.
   */
  Board(int rowS,int columnS);
  /*
   * Prints the current state of the board.
   */
  void print();
  /*
   * Returns the board table array.
   */
  char** getBoardTable();
  /*
   * Receives a boardtable in order to update the current board.
   */
  void setBoardTable(char** boardtable);
  /*
   * returns the number of rows in the board.
   */
  int getRowSize();
  /*
   * returns the number of columns in the board.
   */
  int getColumnSize();
  /*
   * destructor - deletes the dynamic allocated boardtable_.
   */
  virtual ~Board();
private:
  char** board_table_;
  int row_size_;
  int column_size_;
};

#endif /* BOARD_H_ */
