#ifndef LINESEGMENT_HPP_
#define LINESEGMENT_HPP_

#include "SFML/Graphics/Color.hpp"
#include "drawable.hpp"
#include "point2d.hpp"

class LineSegment : Drawable {
  Point2d m_start;
  Point2d m_end;
  sf::Color m_color{};

public:
  LineSegment(Point2d start, Point2d end, sf::Color color = {});

  void draw();

  Point2d getStart() const;
  Point2d getEnd() const;

  void setA(Point2d val);
  void setB(Point2d val);
  void setColor(sf::Color color);
};

#endif // LINESEGMENT_HPP_
