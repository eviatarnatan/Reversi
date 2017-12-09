/*
 * Eviatar Natan
 * 307851808
 */
/*
 * Point.h
 *
 *  Created on: Nov 3, 2017
 *      Author: eviatar
 */

#ifndef POINT_H_
#define POINT_H_
/*
 * defines a point.
 */
class Point {
public:
  /*
   * the constructor - receives two points and sets them as
   * the x and y value of the new created point.
   */
  Point(int x_index, int y_index);
  /*
   * returns the x value of the point.
   */
  int getPointX();
  /*
   * returns the y value of the point.
   */
  int getPointY();
  /*
   * sets a new x value to the point.
   */
  void setPointX(int x_index);
  /*
   * sets a new y value to the point.
   */
  void setPointY(int y_index);
  /*
   * the default destructor.
   */
  virtual ~Point();
private:
  double x_;
  double y_;
};

#endif /* POINT_H_ */
