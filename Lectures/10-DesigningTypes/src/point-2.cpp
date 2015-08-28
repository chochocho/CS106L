// Define our includes and namespace
#include <iostream>
#include <cmath>
using namespace std;

// Define the interface of our type
struct Point {
  double x, y;
};

void printPoint(Point& p) {
  cout << "x: " << p.x << endl;
  cout << "y: " << p.y << endl;
}

void printPointPolar(Point& p) {
  cout << "r: " << sqrt(p.x*p.x + p.y*p.y) << endl;
  cout << "\u0398: " << atan2(p.y, p.x) << endl;
}

// Define the implementation of our type

// empty

// Define our program
int main() {
  Point z;
  z.x = 1;
  z.y = 1;
  printPoint(z);
  printPointPolar(z);
}
