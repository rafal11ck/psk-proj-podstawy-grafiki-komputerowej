#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Color.hpp"
#include "drawable.hpp"

class Circle : public Drawable {
  sf::CircleShape m_shape{};

public:
  Circle &setColor(sf::Color color) {
    m_shape.setOutlineColor(color);
    return *this;
  };
  Circle &setFillColor(sf::Color fillColor) {
    m_shape.setFillColor(fillColor);
    return *this;
  };

  void draw() const;
};

#endif // CIRCLE_H_
