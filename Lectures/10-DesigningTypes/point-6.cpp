// Define our includes and namespace
#include <iostream>
#include <cmath>
using namespace std;

// Define the interface of our type
struct Point {
  double x, y;
  static const double kPi;
  void print();
  void printPolar();
  double radToDeg(double radians);
  void normalize();
};

// Define the implementation of our type
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
  cout << "\u0398: " << radToDeg(atan2(y, x)) << " degrees" << endl;
}

void Point::normalize() {
  double magnitude = sqrt(x*x + y*y);
  x /= magnitude;
  y /= magnitude;
}

// Define our program
int main() {
  Point z;
  z.x = 1;
  z.y = 1;
  z.normalize();
  z.print();
  z.printPolar();
}
