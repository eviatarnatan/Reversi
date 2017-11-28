/*
 * AiPlayer.cpp
 *
 *  Created on: Nov 24, 2017
 *      Author: eviatar
 */

#include "AiPlayer.h"
#include <iostream>
AiPlayer::AiPlayer() {
  // TODO Auto-generated constructor stub
  disks_num_ = 2;
  my_turn_ = false;
  symbol_ = 'O';
  other_symbol_ = 'X';
}
int AiPlayer::getDisksNum() {
  return disks_num_;
}
void AiPlayer::setDisksNum(int disks_num) {
  disks_num_ = disks_num_ + disks_num;
}
bool AiPlayer::getMyTurn() {
  return my_turn_;
}
void AiPlayer::setMyTurn(bool status) {
  my_turn_ = status;
}
char AiPlayer::getSymbol() {
  return symbol_;
}
void AiPlayer::setSymbol(char symbol) {
  symbol_ = symbol;
}
char AiPlayer::getOppositeSymbol() {
  return symbol_;
}
void AiPlayer::setOppositeSymbol(char other_symbol) {
  other_symbol_ = other_symbol;
}
void AiPlayer::turn(GameLogic*& logic, Board*& board, Player*& other) {
 vector<Point> possiblemoves;
 vector<Point>& ref=possiblemoves;
 char &symbol = symbol_;
 char &othersymbol = other_symbol_;
 cout << symbol_ <<": It's the computer move." << endl;
 logic->availableMoves(ref, board, symbol, othersymbol);
 if (possiblemoves.empty() == false) {
   logic->sortPoints(ref);
   logic->removeDuplicatePoints(ref);
   cout << "The computer possible moves: ";
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
 //contains max possible score for human player for each Ai move.
 vector<int> bestAiMoves;
 //for each possible move of the computer
 for (unsigned int i=0;i<possiblemoves.size();i++){
	 //lowest score possible
	 int score=-64;
	 Board *tempboard=new Board(board->getRowSize(),board->getColumnSize());
	 char **boardarray=board->getBoardTable();
	 char **temparray=tempboard->getBoardTable();
	 //copy cells content from main board to temp board
	 for (int i=0;i<board->getRowSize();i++){
		 for (int j=0;j<board->getColumnSize();j++) {
			 temparray[i][j]=boardarray[i][j];
		 }
	 }
	 //tempboard->print();
		 Point point(possiblemoves.at(i).getPointX(),
				 possiblemoves.at(i).getPointY());
		 Point &refpoint=point;
		 //flip current computer move
		 logic->flipDiscs(tempboard,refpoint,symbol,othersymbol);
		 //tempboard->print();
		 vector<Point> humanmoves;
		 vector<Point>&humanmovesref=humanmoves;
		 //check human player possible moves
		 logic->availableMoves(humanmovesref,tempboard,othersymbol,symbol);
		 logic->sortPoints(humanmovesref);
		 logic->removeDuplicatePoints(humanmovesref);
		 //for each possible human move
		 for (unsigned int i=0;i<humanmoves.size();i++) {
			 int humandiscs=0;
			 int aidiscs=0;
			 Board *humantempboard=new Board(board->getRowSize(),board->getColumnSize());
			 char**tempboardhuman=humantempboard->getBoardTable();
			 vector<int> movemark;
			 //give the human board the current move of the computer
			 for (int i=0;i<board->getRowSize();i++){
				 for (int j=0;j<board->getColumnSize();j++) {
					 tempboardhuman[i][j]=temparray[i][j];
				 }
			 }
			 Point currentHumanMove(humanmoves.at(i).getPointX(),
					 humanmoves.at(i).getPointY());
			 Point &humanMoveRef=currentHumanMove;
			 logic->flipDiscs(humantempboard,humanMoveRef,othersymbol,symbol);
			 //humantempboard->print();
			 for (int i=0;i<humantempboard->getRowSize();i++){
				 for (int j=0;j<humantempboard->getColumnSize();j++) {
					 if (tempboardhuman[i][j]=='X') {
						 humandiscs++;
					 }
					 if (tempboardhuman[i][j]=='O') {
						 aidiscs++;
					 }
				 }
			 }
			 if (humandiscs-aidiscs>score) {
				 score=humandiscs-aidiscs;
			 }
			 //clean last human board - go to next human move
			 for (int i=0;i<board->getRowSize();i++){
				 for (int j=0;j<board->getColumnSize();j++) {
					 tempboardhuman[i][j]=temparray[i][j];
				 }
			 }
			 int xpoint=point.getPointX()-1;
			 int ypoint=point.getPointY()-1;
			 temparray[xpoint][ypoint]= 'O';
			 //tempboard->print();
		 }
		 bestAiMoves.push_back(score);
		 //delete bestmove;
 }
 int max=0;
 int bestmoveindex=0;
 //find the maximum score for human player
 for (unsigned int i=0;i<bestAiMoves.size();i++){
	 if (bestAiMoves.at(i)>max) {
		 max=bestAiMoves.at(i);
	 }
 }
 for (unsigned int i=0;i<bestAiMoves.size();i++) {
	 if (bestAiMoves.at(i)<max) {
		 max=bestAiMoves.at(i);
		 bestmoveindex=i;
	 }
 }
 Point point(possiblemoves.at(bestmoveindex).getPointX(),
		 possiblemoves.at(bestmoveindex).getPointY());
 Point &refPoint = point;
 int counter = 0;
 //set counter with the current amount of flips occured this turn.
 counter = logic->flipDiscs(board,refPoint,symbol,othersymbol);
 setDisksNum(1+counter);
 other->setDisksNum(-counter);
 cout << symbol_ << " played (" << point.getPointX() << "," << point.getPointY() << ")" << endl <<endl;
}
AiPlayer::~AiPlayer() {
	// TODO Auto-generated destructor stub
}
/*bool legal = false;
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
   for (int i = 0; i < possiblemoves.size(); i++) {
     if (possiblemoves.at(i).getPointX() == row) {
       if (possiblemoves.at(i).getPointY() == column ) {
         legal = true;
       }
     }
   }
   if (legal == true)
       break;
   cout << "illegal move. choose another:";
 }*/
