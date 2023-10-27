#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "SFML/Graphics/Color.hpp"
#include "drawable.hpp"
#include "point2d.hpp"
#include "primitiveRenderer.hpp"

class Circle : public Drawable {
  Point2d m_origin{};
  int m_radius{};
  sf::Color m_color{PrimitiveRenderer::s_defaultColor};
  sf::Color m_fillColor{sf::Color::Transparent};

public:
  void setColor(sf::Color color) { m_color = color; };
  void setFillColor(sf::Color fillColor) { m_fillColor = fillColor; };

  void draw() const;
};

#endif // CIRCLE_H_
