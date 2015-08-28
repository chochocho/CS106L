// Define our includes and namespace
#include "point.h"
// Notice that we don't have to include iostream

// Define our program
int main() {
  Point z(1,1);
  z.print();
  z.normalize();
  z.print();
  z.printPolar();
}
