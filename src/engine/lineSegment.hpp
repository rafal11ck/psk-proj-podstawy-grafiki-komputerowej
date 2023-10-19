#ifndef LINESEGMENT_HPP_
#define LINESEGMENT_HPP_

#include "drawable.hpp"
#include "point2d.hpp"

class LineSegment : Drawable {
  Point2d m_a;
  Point2d m_b;

public:
  void draw();

  Point2d getA() const;
  Point2d getB() const;

  void setA(Point2d val);
  void setB(Point2d val);
};

#endif // LINESEGMENT_HPP_
