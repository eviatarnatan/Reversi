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
Board::Board(int rowS,int columnS) {
  rowsize_ = rowS;
  columnsize_ = columnS;
  boardtable_ = new char*[rowsize_];
  for (int i = 0; i < rowsize_; ++i) {
      boardtable_[i] = new char[columnsize_];
    }
  for (int i = 0; i < rowsize_; ++i) {
    for (int j = 0;j < columnsize_; ++j) {
      boardtable_[i][j] = ' ';
    }
  }
  boardtable_[rowsize_/2-1][columnsize_/2-1] = 'O';
  boardtable_[rowsize_/2-1][columnsize_/2] = 'X';
  boardtable_[rowsize_/2][columnsize_/2-1] = 'X';
  boardtable_[rowsize_/2][columnsize_/2] = 'O';
}

void Board::print() {
  cout << "Current board:" << endl << endl;
  for (int i = 1; i < columnsize_ + 1; i++){
    cout << " | " << i;
  }
  cout << " |" << endl;
  cout << "--";
  for (int i = 0; i < columnsize_; i++){
    cout << "----";
  }
  cout << endl;
  for (int i = 0; i < rowsize_; ++i) {
    cout << i+1 << "| ";
    for (int j = 0; j < columnsize_; ++j) {
      cout << boardtable_[i][j] << " | ";
    }
    cout << endl;
    cout << "--";
    for (int i = 0; i < columnsize_; i++){
    cout << "----";
    }
    cout << endl;
  }
}

char** Board::getBoardTable() {
  return boardtable_;
}
void Board::setBoardTable(char** table) {
  boardtable_ = table;
}
int Board::getRowSize() {
  return rowsize_;
}
int Board::getColumnSize() {
  return columnsize_;
}
Board::~Board() {
  for (int i=0;i<rowsize_;++i) {
    delete [] boardtable_[i];
  }
  delete [] boardtable_;
}

