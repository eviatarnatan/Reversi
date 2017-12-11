/*
 * Eviatar Natan
 * 307851808
 */
/*
 * AllTests.cpp
 *
 *  Created on: Nov 28, 2017
 *      Author: eviatar
 */
#include "gtest/gtest.h"
#include "BoardTests.cpp"
#include "LogicTests.cpp"
#include "PlayerTests.cpp"
#include "PointClassTests.cpp"

//#include "LogicTests.cpp"

int main (int argc,char **argv) {
	::testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}


