/*
 * Eviatar Natan
 * 307851808
 */
/*
 * HumanPlayer.cpp
 *
 *  Created on: Nov 24, 2017
 *      Author: eviatar
 */

#include "HumanPlayer.h"
#include <iostream>
HumanPlayer::HumanPlayer(char symbol,char other_symbol) {
  // TODO Auto-generated constructor stub
  disks_num_ = 2;
  my_turn_ = false;
  symbol_ = symbol;
  other_symbol_ = other_symbol;
}
int HumanPlayer::getDisksNum() {
  return disks_num_;
}
void HumanPlayer::setDisksNum(int disks_num) {
  disks_num_ = disks_num_ + disks_num;
}
bool HumanPlayer::getMyTurn() {
  return my_turn_;
}
void HumanPlayer::setMyTurn(bool status) {
  my_turn_ = status;
}
char HumanPlayer::getSymbol() {
  return symbol_;
}
void HumanPlayer::setSymbol(char symbol) {
  symbol_ = symbol;
}
char HumanPlayer::getOppositeSymbol() {
  return other_symbol_;
}
void HumanPlayer::setOppositeSymbol(char other_symbol) {
  other_symbol_ = other_symbol;
}
void HumanPlayer::turn(GameLogic*& logic, Board*& board, Player*& other) {
 int row, column;
 vector<Point> possible_moves;
 vector<Point>& moves_ref=possible_moves;
 char &symbol = symbol_;
 char &other_symbol = other_symbol_;
 cout << symbol_ << ": It's your move." << endl;
 logic->availableMoves(moves_ref, board, symbol, other_symbol);
 if (possible_moves.empty() == false) {
   logic->sortPoints(moves_ref);
   logic->removeDuplicatePoints(moves_ref);
   cout << "Your possible moves: ";
   //print available moves
   for (unsigned int i = 0; i < possible_moves.size(); i++) {
     if (i > 0) {
       cout << ",";
     }
     cout << "(" << possible_moves.at(i).getPointX() << "," <<
         possible_moves.at(i).getPointY() << ")";
   }
   cout << endl << endl;
 }
 //in case there are no avaiable moves.
 else{
   cout << "no possible moves. play passes back to the other player." << endl;
   setMyTurn(false);
   return;
 }
 bool legal = false;
 cout << "Please enter your move row col:";
 while (true){
   while (true){
     cin >> row >> column;
     if (!cin.fail()){
       //skip bad input
       cin.ignore(256, '\n');
       break;
     }
     else{
       // user didn't input a number/bad number and char combo
       cout << "Please enter numbers only." << endl;
       cin.clear();
       cin.ignore(256, '\n');
     }
   }
   for (unsigned int i = 0; i < possible_moves.size(); i++) {
     if (possible_moves.at(i).getPointX() == row) {
       if (possible_moves.at(i).getPointY() == column ) {
         legal = true;
       }
     }
   }
   if (legal == true)
       break;
   cout << "illegal move. choose another:";
 }
 Point point(row,column);
 Point &ref_point = point;
 int counter = 0;
 //set counter with the current amount of flips occured this turn.
 counter = logic->flipDiscs(board,ref_point,symbol,other_symbol);
 setDisksNum(1+counter);
 other->setDisksNum(-counter);
 board->print();
 cout << symbol_ << " played (" << row << "," << column << ")" << endl << endl;
}
HumanPlayer::~HumanPlayer() {
	// TODO Auto-generated destructor stub
}

