#ifndef LINESEGMENT_HPP_
#define LINESEGMENT_HPP_

#include "drawable.hpp"
#include "point2d.hpp"

class LineSegment : Drawable {
  Point2d m_start;
  Point2d m_end;

public:
  void draw();

  Point2d getStart() const;
  Point2d getEnd() const;

  void setA(Point2d val);
  void setB(Point2d val);
};

#endif // LINESEGMENT_HPP_
