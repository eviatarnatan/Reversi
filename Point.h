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
  Point(double x_index, double y_index);
  /*
   * returns the x value of the point.
   */
  double getPointX();
  /*
   * returns the y value of the point.
   */
  double getPointY();
  /*
   * sets a new x value to the point.
   */
  void setPointX(double x_index);
  /*
   * sets a new y value to the point.
   */
  void setPointY(double y_index);
  /*
   * the default destructor.
   */
  virtual ~Point();
private:
  double x_;
  double y_;
};

#endif /* POINT_H_ */
