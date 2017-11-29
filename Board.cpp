/*
 * Eviatar Natan
 * 307851808
 */
/*
 * Board.cpp
 *
 *  Created on: Oct 22, 2017
 *      Author: eviatar
 */

#include "Board.h"
#include <iostream>
using namespace std;
Board::Board(int row_size,int column_size) {
  row_size_ = row_size;
  column_size_ = column_size;
  board_table_ = new char*[row_size_];
  for (int i = 0; i < row_size_; ++i) {
      board_table_[i] = new char[column_size_];
    }
  for (int i = 0; i < row_size_; ++i) {
    for (int j = 0;j < column_size_; ++j) {
      board_table_[i][j] = ' ';
    }
  }
  board_table_[row_size_/2-1][column_size_/2-1] = 'O';
  board_table_[row_size_/2-1][column_size_/2] = 'X';
  board_table_[row_size_/2][column_size_/2-1] = 'X';
  board_table_[row_size_/2][column_size_/2] = 'O';
}

void Board::print() {
  cout << "Current board:" << endl << endl;
  for (int i = 1; i < column_size_ + 1; i++){
    cout << " | " << i;
  }
  cout << " |" << endl;
  cout << "--";
  for (int i = 0; i < column_size_; i++){
    cout << "----";
  }
  cout << endl;
  for (int i = 0; i < row_size_; ++i) {
    cout << i+1 << "| ";
    for (int j = 0; j < column_size_; ++j) {
      cout << board_table_[i][j] << " | ";
    }
    cout << endl;
    cout << "--";
    for (int i = 0; i < column_size_; i++){
    cout << "----";
    }
    cout << endl;
  }
}

char** Board::getBoardTable() {
  return board_table_;
}
void Board::setBoardTable(char** table) {
  board_table_ = table;
}
int Board::getRowSize() {
  return row_size_;
}
int Board::getColumnSize() {
  return column_size_;
}
Board::~Board() {
  for (int i=0;i<row_size_;++i) {
    delete [] board_table_[i];
  }
  delete [] board_table_;
}

