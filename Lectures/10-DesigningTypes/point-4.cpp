// Define our includes and namespace
#include <iostream>
#include <cmath>
using namespace std;

// Define the interface of our type
struct Point {
  double x, y;
  void print();
  void printPolar();
  double radToDeg(double radians);
};


// Define the implementation of our type

// Notice that we've added a global constant
const double kPi = 3.14159265;

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

// Define our program
int main() {
  Point z;
  z.x = 1;
  z.y = 1;
  z.print();
  z.printPolar();
}
