#include "lineSegment.hpp"
#include "SFML/Graphics/Color.hpp"
#include "point2d.hpp"
#include "primitiveRenderer.hpp"

LineSegment::LineSegment(Point2d start, Point2d end, sf::Color color)
    : m_start{start}, m_end{end} {}

void LineSegment::draw() {
  PrimitiveRenderer::drawLine(m_start, m_end, m_color);
}

Point2d LineSegment::getStart() const { return m_start; }
Point2d LineSegment::getEnd() const { return m_end; }

void LineSegment::setA(Point2d val) { m_start = val; }
void LineSegment::setB(Point2d val) { m_end = val; }

void LineSegment::setColor(sf::Color color) { m_color = color; }
