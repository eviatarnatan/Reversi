/*
 * Eviatar Natan
 * 307851808
 */
/*
 * PointClassTests.cpp
 *
 *  Created on: Nov 30, 2017
 *      Author: eviatar
 */

#include "gtest/gtest.h"
#include "Point.h"

namespace {
	/*
	 * getting a point test.
	 */
	TEST(PointClassTests, returned_point_test) {
		Point p(3,5);
		EXPECT_EQ(3, p.getPointX());
		EXPECT_EQ(5, p.getPointY());
		p.setPointX(5);
		EXPECT_NE(3,p.getPointX());
		p.setPointY(7);
		EXPECT_NE(5,p.getPointY());
	}
}
