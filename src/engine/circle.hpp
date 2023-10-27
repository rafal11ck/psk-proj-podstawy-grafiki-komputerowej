#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Color.hpp"
#include "drawable.hpp"
#include "point2d.hpp"

class Circle : public Drawable {

  sf::CircleShape m_shape{};

public:
  Circle(float radius = {}, Point2d position = {}, Color fillColor = {},
         Color outlineColor = {});

  Circle &setOutlineColor(Color color);

  Circle &setFillColor(Color fillColor);

  Circle &setPosition(const Point2d &point);

  Circle &setRadius(float radius);

  void draw() const;
};

#endif // CIRCLE_H_
