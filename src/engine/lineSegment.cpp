#include "lineSegment.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/Graphics/Vertex.hpp"
#include "engine.hpp"
#include "point2d.hpp"
#include "primitiveRenderer.hpp"

LineSegment::LineSegment(Point2d start, Point2d end, sf::Color color)
    : m_points{{start.toVector2f(), color}, {end.toVector2f(), color}},
      m_color{color} {};

void LineSegment::draw() const {
  Engine::getInstance().getWindow().draw(m_points, 2, sf::Lines);
}

Point2d LineSegment::getStart() const { return Point2d{m_points[0].position}; }
Point2d LineSegment::getEnd() const { return Point2d{m_points[1].position}; }

void LineSegment::setStart(Point2d val) {
  m_points[0].position = val.toVector2f();
}
void LineSegment::setEnd(Point2d val) {
  m_points[1].position = val.toVector2f();
}
