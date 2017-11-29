/*
 * BoardTest.cpp
 *
 *  Created on: Nov 28, 2017
 *      Author: eviatar
 */
#include "gtest/gtest.h"
#include "Game.h"

namespace {
	/*
	 * board initialization test
	 */
	TEST(GameTests, board_test) {
		const int size = 8;
		Board *board = new Board(size, size);
		char **boardtable = board->getBoardTable();
		EXPECT_EQ(size, board->getRowSize());
		EXPECT_NE(size + 1, board->getColumnSize());
		EXPECT_EQ('O', boardtable[size / 2][size / 2]);
		EXPECT_NE('X', boardtable[size / 2 - 1][size / 2 - 1]);
		delete board;
	}
	/*
	 * check available moves for certain board configuration
	 */
	TEST(GameTests, game_logic_available_moves_test) {
		const int size = 8;
		const unsigned int number_of_moves = 5;
		Board *board = new Board(size,size);
		char **boardtable = board->getBoardTable();
		GameLogic *logic = new ReversiLogic;
		char symbol = 'X';
		char other_symbol = 'O';
		char &symbol_ref = symbol;
		char &other_symbol_ref = other_symbol;
		vector<Point> available_moves;
		vector<Point> &move_ref = available_moves;
		boardtable[2][2] = 'O';
		boardtable[2][3] = 'O';
		boardtable[2][4] = 'O';
		boardtable[4][4] = 'X';
		boardtable[4][5] = 'X';
		logic->availableMoves(move_ref, board, symbol_ref, other_symbol_ref);
		logic->sortPoints(move_ref);
		logic->removeDuplicatePoints(move_ref);
		Point p(5, 3);
		bool found = false;
		for (unsigned int i = 0; i < available_moves.size(); i++) {
			if (available_moves.at(i).getPointX() == p.getPointX()
					&& available_moves.at(i).getPointY() == p.getPointY()) {
				found = true;
			}
		}
		EXPECT_FALSE(found);
		//checks if certain moves are available and at a correct vector index.
		Point p1(2, 2), p2(2, 5), p3(4, 3);
		EXPECT_EQ(number_of_moves, available_moves.size());
		EXPECT_EQ(p1.getPointX(), available_moves.at(0).getPointX());
		EXPECT_EQ(p1.getPointY(), available_moves.at(0).getPointY());
		EXPECT_EQ(p2.getPointX(), available_moves.at(3).getPointX());
		EXPECT_EQ(p2.getPointY(), available_moves.at(3).getPointY());
		EXPECT_EQ(p3.getPointX(), available_moves.at(4).getPointX());
		EXPECT_EQ(p3.getPointY(), available_moves.at(4).getPointY());
		delete logic;
		delete board;

	}
	/*
	 * checks that duplicate moves are removed.
	 */
	TEST(GameTests,game_logic_remove_duplicate_points_test) {
		GameLogic *logic = new ReversiLogic();
		vector<Point> available_moves;
		vector <Point> &ref = available_moves;
		Point p1(7, 8);
		Point p2(7, 8);
		Point p3(8, 8);
		Point p4(8, 8);
		available_moves.push_back(p1);
		available_moves.push_back(p2);
		available_moves.push_back(p3);
		available_moves.push_back(p4);
		logic->removeDuplicatePoints(ref);
		EXPECT_TRUE(available_moves.size() == 2);
		delete logic;
	}
	/*
	 * checks that for a specific board state, the computer chooses it's best move
	 * note: best move is defined as the first move in the Ai move list, which
	 * the other player will get the minimum amount of points for it.
	 */
	TEST(GameTests, AI_test) {
		const int size = 8;
		Board *board = new Board(size,size);
		char **boardtable = board->getBoardTable();
		GameLogic *logic = new ReversiLogic;
		Player *human = new HumanPlayer();
		Player *computer = new AiPlayer();
		boardtable[2][3] = 'X';
		boardtable[3][3] = 'X';
		computer->turn(logic, board, human);
		EXPECT_EQ('O', boardtable[2][2]);
		EXPECT_NE('X', boardtable[3][3]);
		delete board;
		delete logic;
		delete human;
		delete computer;
	}
}



