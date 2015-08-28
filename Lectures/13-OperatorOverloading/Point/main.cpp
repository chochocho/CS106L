#include "point.h"
#include <iostream>
using namespace std;

int main() {
  Point p1(41, 17);
  Point p2(35, 25);
  Point p3 = p1 + p2;
  cout << "Adding points (41, 17) and (35, 25)" << endl;
  p3.print();
  cout << "Multiplying 3 * point(35, 25)" << endl;
  Point p4 =  3*p2*3;
  p4.print();
}
