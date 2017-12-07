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

Point::Point(double x_index, double y_index) {
  // TODO Auto-generated constructor stub
  x_=x_index;
  y_=y_index;
}
double Point::getPointX() {
  return x_;
}
double Point::getPointY() {
  return y_;
}
void Point::setPointX(double x_index) {
  x_=x_index;
}
void Point::setPointY(double y_index) {
  y_=y_index;
}
Point::~Point() {
  // TODO Auto-generated destructor stub
}

