// Define our includes and namespace
#include <iostream>
#include <cmath>
using namespace std;

// Define the interface of our type
#include "point.h"

// Define the implementation of our type
Point::Point() {
  x = 0.0;
  y = 0.0;
}

Point::Point(double xVal, double yVal) {
  x = xVal;
  y = yVal;
}

const double Point::kPi = 3.14159265;

void Point::print() const {
  cout << "x: " << x << endl;
  cout << "y: " << y << endl;
}

double Point::radToDeg(double radians) const {
  return radians * 180.0 / kPi;
}

void Point::printPolar() const {
  cout << "r: " << sqrt(x*x + y*y) << endl;
  cout << "\u0398: " << radToDeg(atan2(y, x)) << " degrees" << endl;
}

void Point::normalize() {
  double magnitude = sqrt(x*x + y*y);
  x /= magnitude;
  y /= magnitude;
}

Point Point::operator+(const Point & otherPoint) const{
  Point returnPoint(otherPoint.x + x, otherPoint.y + y);
  return returnPoint;
}

Point Point::operator*(const double scaleFactor) const{
  Point returnPoint(x * scaleFactor, y * scaleFactor);
  return returnPoint;
}

Point operator*(const double scaleFactor, 
                const Point & point) {
  Point returnPoint(point.x * scaleFactor, 
                    point.y * scaleFactor);
  return returnPoint;
}







