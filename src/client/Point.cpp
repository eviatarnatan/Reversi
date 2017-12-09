/*
 * Eviatar Natan
 * 307851808
 */
/*
 * Point.cpp
 *
 *  Created on: Nov 3, 2017
 *      Author: eviatar
 */

#include "Point.h"

Point::Point(int x_index, int y_index) {
  // TODO Auto-generated constructor stub
  x_=x_index;
  y_=y_index;
}
int Point::getPointX() {
  return x_;
}
int Point::getPointY() {
  return y_;
}
void Point::setPointX(int x_index) {
  x_=x_index;
}
void Point::setPointY(int y_index) {
  y_=y_index;
}
Point::~Point() {
  // TODO Auto-generated destructor stub
}

