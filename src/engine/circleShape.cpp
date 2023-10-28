
#include "circle.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "engine.hpp"

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

void CircleShape::draw() const {
  Engine::getInstance().getWindow().draw(m_shape);
}
