/*
 * AllTests.cpp
 *
 *  Created on: Nov 28, 2017
 *      Author: eviatar
 */
#include "gtest/gtest.h"

#include "GameTests.cpp"

int main (int argc,char **argv) {
	::testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}


