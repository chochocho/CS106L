// Define the interface of our type
#pragma once // Ignore this line for now!
class Point {
  public:
  Point();
  Point(double xVal, double yVal);

  void print();
  void printPolar();
  void normalize();
  private: 
  double radToDeg(double radians);
  double x, y;
  static const double kPi;
};
