#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Color.hpp"
#include "drawable.hpp"
#include "point2d.hpp"

class CircleShape : public Drawable {

  sf::CircleShape m_shape{};

public:
  CircleShape(float radius = {}, Point2d position = {}, Color fillColor = {},
              Color outlineColor = {});

  CircleShape &setOutlineColor(Color color);

  CircleShape &setFillColor(Color fillColor);

  CircleShape &setPosition(const Point2d &point);

  CircleShape &setRadius(float radius);

  void draw() const;
};

#endif // CIRCLE_H_
