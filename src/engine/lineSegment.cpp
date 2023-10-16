#include "lineSegment.hpp"
#include "point2d.hpp"
#include "primitiveRenderer.hpp"

void LineSegment::draw() { PrimitiveRenderer::drawLine(m_a, m_b); }

Point2d LineSegment::getA() const { return m_a; }
Point2d LineSegment::getB() const { return m_b; }

void LineSegment::setA(Point2d val) { m_a = val; }
void LineSegment::setB(Point2d val) { m_b = val; }
