#ifndef CIRCLESHAPE_H_
#define CIRCLESHAPE_H_

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Color.hpp"
#include "drawable.hpp"
#include "point2d.hpp"
#include "shape.hpp"

/**
 *@file
 *@deprecated Bad design. Reinventing wheel.
 **/

namespace obstacle {
class CircleShape : public Shape {

  sf::CircleShape m_shape{};

public:
  CircleShape(float radius = {}, Point2d position = {}, Color fillColor = {},
              Color outlineColor = {});

  CircleShape &setOutlineColor(Color color);

  CircleShape &setFillColor(Color fillColor);

  CircleShape &setPosition(const Point2d &point);

  CircleShape &setRadius(float radius);

  Point2d getPosition() const;
  void draw() const;
};

};     // namespace obstacle
#endif // CIRCLESHAPE_H_
