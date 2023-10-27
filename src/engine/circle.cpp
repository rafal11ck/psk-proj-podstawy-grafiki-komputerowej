
#include "circle.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Shape.hpp"
#include "engine.hpp"

void Circle::draw() const {
  sf::CircleShape circle{};
  circle.setPosition(m_origin.getX(), m_origin.getY());
  circle.setRadius(m_radius);
  circle.setOutlineColor(m_color);
  circle.setFillColor(m_fillColor);
  Engine::getInstance().getWindow().draw(circle);
}
