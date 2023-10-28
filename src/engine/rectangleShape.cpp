#include "rectangleShape.hpp"
#include "drawable.hpp"
#include "engine.hpp"
#include "point2d.hpp"

RectangleShape::RectangleShape(Point2d position, Point2d size, Color fillColor,
                               Color outlineColor) {
  setPosition(position);
  setSize(size);
  setFillColor(fillColor);
  setOutlineColor(outlineColor);
}

RectangleShape &RectangleShape::setOutlineColor(Color color) {
  m_shape.setOutlineColor(color);
  return *this;
};

RectangleShape &RectangleShape::setFillColor(Color fillColor) {
  m_shape.setFillColor(fillColor);
  return *this;
};

Drawable &RectangleShape::setPosition(const Point2d &position) {
  m_shape.setPosition(position.toVector2f());
  return *this;
};

RectangleShape &RectangleShape::setSize(Point2d size) {
  m_shape.setSize(size.toVector2f());
  return *this;
};

Point2d RectangleShape::getPosition() const {
  return Point2d{m_shape.getPosition()};
}

void RectangleShape::draw() const {
  Engine::getInstance().getWindow().draw(m_shape);
}
