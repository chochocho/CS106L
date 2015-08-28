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

void Point::print() {
  cout << "x: " << x << endl;
  cout << "y: " << y << endl;
}

double Point::radToDeg(double radians) {
  return radians * 180.0 / kPi;
}

void Point::printPolar() {
  cout << "r: " << sqrt(x*x + y*y) << endl;
  cout << "theta: " << radToDeg(atan2(y, x)) << " degrees" << endl;
}

void Point::normalize() {
  double magnitude = sqrt(x*x + y*y);
  x /= magnitude;
  y /= magnitude;
}
