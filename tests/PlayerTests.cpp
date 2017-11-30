/*
 * Eviatar Natan
 * 307851808
 */
/*
 * PlayerTests.cpp
 *
 *  Created on: Nov 30, 2017
 *      Author: eviatar
 */
#include "gtest/gtest.h"
#include "Game.h"

namespace {
/*
 * checks that for a specific board state, the computer chooses it's best move
 * note: best move is defined as the first move in the Ai move list, which
 * the other player will get the minimum amount of points for it.
 */
TEST(PlayerTests, AI_test) {
	const int size = 8;
	Board *board = new Board(size,size);
	char **boardtable = board->getBoardTable();
	GameLogic *logic = new ReversiLogic;
	Player *human = new HumanPlayer('X', 'O');
	Player *computer = new AiPlayer('O', 'X');
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
/*
 * checks returned player turn status is correct.
 */
TEST(PlayerTests, turns_test) {
	Player *human = new HumanPlayer('X', 'O');
	Player *computer = new AiPlayer('O', 'X');
	human->setMyTurn(true);
	EXPECT_TRUE(human->getMyTurn());
	EXPECT_FALSE(computer->getMyTurn());
	delete human;
	delete computer;
}
/*
 * checks get symbols of each player.
 */
TEST(PlayerTests, player_playing_symbol_test) {
	Player *human = new HumanPlayer('X', 'O');
	Player *computer = new AiPlayer('O', 'X');
	EXPECT_EQ('X', human->getSymbol());
	EXPECT_EQ('O', human->getOppositeSymbol());
	EXPECT_EQ('O', computer->getSymbol());
	EXPECT_EQ('X', computer->getOppositeSymbol());
	delete human;
	delete computer;
}
/*
 * tests the number of discs of each player.
 * note: each player starts with 2 discs.
 */
TEST(PlayerTests, player_symbol_test) {
	Player *human = new HumanPlayer('X', 'O');
	Player *computer = new AiPlayer('O', 'X');
	human->setDisksNum(13);
	computer->setDisksNum(7);
	EXPECT_EQ(15, human->getDisksNum());
	EXPECT_EQ(9, computer->getDisksNum());
	human->setDisksNum(-8);
	computer->setDisksNum(-2);
	EXPECT_EQ(human->getDisksNum(), computer->getDisksNum());
	delete human;
	delete computer;
}
}
