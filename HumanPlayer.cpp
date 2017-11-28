/*
 * HumanPlayer.cpp
 *
 *  Created on: Nov 24, 2017
 *      Author: eviatar
 */

#include "HumanPlayer.h"
#include <iostream>
HumanPlayer::HumanPlayer() {
  // TODO Auto-generated constructor stub
  disks_num_ = 2;
  my_turn_ = false;
  symbol_ = ' ';
  other_symbol_ = ' ';
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
  return symbol_;
}
void HumanPlayer::setOppositeSymbol(char other_symbol) {
  other_symbol_ = other_symbol;
}
void HumanPlayer::turn(GameLogic*& logic, Board*& board, Player*& other) {
 int row, column;
 vector<Point> possiblemoves;
 vector<Point>& ref=possiblemoves;
 //sets 'X' symbol for the first player, 'O' for second
 if (getSymbol() == ' ') {
   setSymbol('X');
   setOppositeSymbol('O');
   other->setSymbol('O');
   other->setOppositeSymbol('X');
 }
 char &symbol = symbol_;
 char &othersymbol = other_symbol_;
 cout << symbol_ <<": It's your move." << endl;
 logic->availableMoves(ref, board, symbol, othersymbol);
 if (possiblemoves.empty() == false) {
   logic->sortPoints(ref);
   logic->removeDuplicatePoints(ref);
   cout << "Your possible moves: ";
   //print available moves
   for (unsigned int i = 0; i < possiblemoves.size(); i++) {
     if (i > 0) {
       cout<<",";
     }
     cout << "(" << possiblemoves.at(i).getPointX() << "," <<
         possiblemoves.at(i).getPointY() << ")";
   }
   cout << endl<<endl;
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
   for (unsigned int i = 0; i < possiblemoves.size(); i++) {
     if (possiblemoves.at(i).getPointX() == row) {
       if (possiblemoves.at(i).getPointY() == column ) {
         legal = true;
       }
     }
   }
   if (legal == true)
       break;
   cout << "illegal move. choose another:";
 }
 Point point(row,column);
 Point &refPoint = point;
 int counter = 0;
 //set counter with the current amount of flips occured this turn.
 counter = logic->flipDiscs(board,refPoint,symbol,othersymbol);
 setDisksNum(1+counter);
 other->setDisksNum(-counter);
 board->print();
 cout << symbol_ << " played (" << row << "," << column << ")" << endl <<endl;
}
HumanPlayer::~HumanPlayer() {
	// TODO Auto-generated destructor stub
}

