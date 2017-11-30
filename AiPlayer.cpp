/*
 * Eviatar Natan
 * 307851808
 */
/*
 * AiPlayer.cpp
 *
 *  Created on: Nov 24, 2017
 *      Author: eviatar
 */

#include "AiPlayer.h"
#include <iostream>
AiPlayer::AiPlayer(char symbol, char other_symbol) {
  // TODO Auto-generated constructor stub
  disks_num_ = 2;
  my_turn_ = false;
  symbol_ = symbol;
  other_symbol_ = other_symbol;
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
  return other_symbol_;
}
void AiPlayer::setOppositeSymbol(char other_symbol) {
  other_symbol_ = other_symbol;
}
void AiPlayer::turn(GameLogic*& logic, Board*& board, Player*& other) {
 vector<Point> possible_moves;
 vector<Point>& ref = possible_moves;
 char &symbol = symbol_;
 char &other_symbol = other_symbol_;
 cout << symbol_ << ": It's the computer move." << endl;
 logic->availableMoves(ref, board, symbol, other_symbol);
 if (possible_moves.empty() == false) {
   logic->sortPoints(ref);
   logic->removeDuplicatePoints(ref);
   cout << "The computer possible moves: ";
   //print available moves
   for (unsigned int i = 0; i < possible_moves.size(); i++) {
     if (i > 0) {
       cout<<",";
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
 //contains max possible score for human player for each Ai move.
 vector<int> best_ai_moves;
 //for each possible move of the computer
 for (unsigned int i = 0; i < possible_moves.size(); i++) {
	 //lowest score possible
	 int score = -64;
	 Board *temp_board = new Board(board->getRowSize(), board->getColumnSize());
	 char **board_array = board->getBoardTable();
	 char **temp_array = temp_board->getBoardTable();
	 //copy cells content from main board to temp board
	 for (int k = 0; k < board->getRowSize(); k++) {
		 for (int j = 0; j < board->getColumnSize(); j++) {
			 temp_array[k][j] = board_array[k][j];
		 }
	 }
		 Point point(possible_moves.at(i).getPointX(),
				 possible_moves.at(i).getPointY());
		 Point &refpoint = point;
		 //flip current computer move
		 logic->flipDiscs(temp_board, refpoint, symbol, other_symbol);
		 vector<Point> human_moves;
		 vector<Point> &human_moves_ref = human_moves;
		 //check human player possible moves
		 logic->availableMoves(human_moves_ref, temp_board, other_symbol, symbol);
		 //for each possible human move
		 for (unsigned int l = 0; l < human_moves.size(); l++) {
			 int human_discs = 0;
			 int ai_discs = 0;
			 Board *human_temp_board = new Board(board->getRowSize(),
					 board->getColumnSize());
			 char**temp_board_human = human_temp_board->getBoardTable();
			 vector<int> movemark;
			 //give the human board the current move of the computer
			 for (int m = 0;m < board->getRowSize(); m++) {
				 for (int j = 0; j < board->getColumnSize(); j++) {
					 temp_board_human[m][j] = temp_array[m][j];
				 }
			 }
			 Point current_human_move(human_moves.at(l).getPointX(),
					 human_moves.at(l).getPointY());
			 Point &human_move_ref = current_human_move;
			 logic->flipDiscs(human_temp_board, human_move_ref,
					 other_symbol, symbol);
			 for (int w = 0; w < human_temp_board->getRowSize(); w++) {
				 for (int j = 0; j < human_temp_board->getColumnSize(); j++) {
					 if (temp_board_human[w][j] == 'X') {
						 human_discs++;
					 }
					 if (temp_board_human[w][j] == 'O') {
						 ai_discs++;
					 }
				 }
			 }
			 if (human_discs - ai_discs > score) {
				 score = human_discs - ai_discs;
			 }
			 //clean last human board - go to next human move
			 for (int v = 0; v < board->getRowSize(); v++){
				 for (int j = 0; j < board->getColumnSize(); j++) {
					 temp_board_human[v][j] = temp_array[v][j];
				 }
			 }
			 int xpoint = point.getPointX() - 1;
			 int ypoint = point.getPointY() - 1;
			 temp_array[xpoint][ypoint] = 'O';
			 delete human_temp_board;
		 }
		 best_ai_moves.push_back(score);
		 delete temp_board;
 }
 int max = 0;
 int best_move_index = 0;
 //find the maximum score for human player
 for (unsigned int i = 0;i < best_ai_moves.size(); i++) {
	 if (best_ai_moves.at(i) > max) {
		 max = best_ai_moves.at(i);
	 }
 }
 for (unsigned int i = 0; i < best_ai_moves.size(); i++) {
	 if (best_ai_moves.at(i) < max) {
		 max = best_ai_moves.at(i);
		 best_move_index = i;
	 }
 }
 Point point(possible_moves.at(best_move_index).getPointX(),
		 possible_moves.at(best_move_index).getPointY());
 Point &ref_point = point;
 int counter = 0;
 //set counter with the current amount of flips occured this turn.
 counter = logic->flipDiscs(board,ref_point,symbol,other_symbol);
 setDisksNum(1+counter);
 other->setDisksNum(-counter);
 board->print();
 cout << symbol_ << " played (" << point.getPointX() << ","
		 << point.getPointY() << ")" << endl <<endl;
}
AiPlayer::~AiPlayer() {
	// TODO Auto-generated destructor stub
}
