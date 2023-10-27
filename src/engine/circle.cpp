
#include "circle.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "engine.hpp"

Circle::Circle(float radius, Point2d position, Color color, Color fillColor) {
  setRadius(radius);
  setPosition(position);
  setOutlineColor(color);
  setFillColor(fillColor);
};

Circle &Circle::setOutlineColor(sf::Color color) {
  m_shape.setOutlineColor(color);
  return *this;
};

Circle &Circle::setFillColor(sf::Color fillColor) {
  m_shape.setFillColor(fillColor);
  return *this;
};

Circle &Circle::setPosition(const Point2d &point) {
  m_shape.setPosition(point.toVector2f());
  return *this;
};

Circle &Circle::setRadius(float radius) {
  m_shape.setRadius(radius);
  return *this;
}

void Circle::draw() const { Engine::getInstance().getWindow().draw(m_shape); }
