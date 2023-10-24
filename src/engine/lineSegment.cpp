#include "lineSegment.hpp"
#include "point2d.hpp"
#include "primitiveRenderer.hpp"

void LineSegment::draw() { PrimitiveRenderer::drawLine(m_start, m_end); }

Point2d LineSegment::getStart() const { return m_start; }
Point2d LineSegment::getEnd() const { return m_end; }

void LineSegment::setA(Point2d val) { m_start = val; }
void LineSegment::setB(Point2d val) { m_end = val; }
