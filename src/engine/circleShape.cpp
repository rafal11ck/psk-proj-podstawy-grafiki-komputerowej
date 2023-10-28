
#include "SFML/Graphics/CircleShape.hpp"
#include "circleShape.hpp"
#include "engine.hpp"
#include "point2d.hpp"

CircleShape::CircleShape(float radius, Point2d position, Color color,
                         Color fillColor) {
  setRadius(radius);
  setPosition(position);
  setOutlineColor(color);
  setFillColor(fillColor);
};

CircleShape &CircleShape::setOutlineColor(sf::Color color) {
  m_shape.setOutlineColor(color);
  return *this;
};

CircleShape &CircleShape::setFillColor(sf::Color fillColor) {
  m_shape.setFillColor(fillColor);
  return *this;
};

CircleShape &CircleShape::setPosition(const Point2d &point) {
  m_shape.setPosition(point.toVector2f());
  return *this;
};

CircleShape &CircleShape::setRadius(float radius) {
  m_shape.setRadius(radius);
  return *this;
}

Point2d CircleShape::getPosition() const {
  return Point2d{m_shape.getPosition()};
}

void CircleShape::draw() const {
  Engine::getInstance().getWindow().draw(m_shape);
}
