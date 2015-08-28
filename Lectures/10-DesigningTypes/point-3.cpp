// Define our includes and namespace
#include <iostream>
#include <cmath>
using namespace std;

// Define the interface of our type
struct Point {
  double x, y;

  void print();
  void printPolar();
};

// Define the implementation of our type
void Point::print() {
  cout << "x: " << x << endl;
  cout << "y: " << y << endl;
}

void Point::printPolar() {
  cout << "r: " << sqrt(x*x + y*y) << endl;
  cout << "\u0398: " << atan2(y, x) << endl;
}

// Define our program
int main() {
  Point z;
  z.x = 1;
  z.y = 1;
  z.print();
  z.printPolar();
}
