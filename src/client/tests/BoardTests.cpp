/*
 * Eviatar Natan
 * 307851808
 */
/*
 * BoardTests.cpp
 *
 *  Created on: Nov 30, 2017
 *      Author: eviatar
 */

#include "gtest/gtest.h"
#include "Board.h"

namespace {
/*
 * board initialization and get parameters test
 */
TEST(BoardTests, board_tests) {
	const int size = 8;
	Board *board = new Board(size, size);
	char **boardtable = board->getBoardTable();
	EXPECT_EQ(size, board->getRowSize());
	EXPECT_NE(size + 1, board->getColumnSize());
	EXPECT_EQ(size , board->getColumnSize());
	EXPECT_EQ('O', boardtable[size / 2][size / 2]);
	EXPECT_NE('X', boardtable[size / 2 - 1][size / 2 - 1]);
	EXPECT_EQ(board->getRowSize(), board->getColumnSize());
	delete board;
	}
}
