#ifndef LINESEGMENT_HPP_
#define LINESEGMENT_HPP_

#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Vertex.hpp"
#include "drawable.hpp"
#include "point2d.hpp"
#include "primitiveRenderer.hpp"
#include "shape.hpp"

/**
 *@file
 *@deprecated Bad design. Reinventing wheel.
 **/

namespace obstacle {
class LineSegment : public Shape {
  sf::Vertex m_points[2] = {};
  sf::Color m_color;

public:
  LineSegment(Point2d start, Point2d end, sf::Color color = {});

  void draw() const;

  Point2d getStart() const;
  Point2d getEnd() const;

  void setStart(Point2d val);
  void setEnd(Point2d val);

  void setColor(sf::Color color) { m_color = color; };
};
};     // namespace obstacle
#endif // LINESEGMENT_HPP_
