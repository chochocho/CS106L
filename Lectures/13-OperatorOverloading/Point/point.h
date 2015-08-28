#pragma once
class Point {
  public:
  Point();
  Point(double xVal, double yVal);

  void print() const;
  void printPolar() const;
  void normalize();
  Point operator+(const Point & otherPoint) const;
  Point operator*(const double scaleFactor) const;
  friend Point operator*(const double scaleFactor, 
                const Point & point);
  
  private: 
  double radToDeg(double radians) const;
  double x, y;
  static const double kPi;
};


