#ifndef RECTANGLESHAPE_H_
#define RECTANGLESHAPE_H_

#include "SFML/Graphics/RectangleShape.hpp"
#include "point2d.hpp"
#include "shape.hpp"

/**
 *@file
 *@deprecated Bad design. Reinventing wheel.
 **/

namespace obstacle {

class RectangleShape : public Shape {
  sf::RectangleShape m_shape{};

public:
  ~RectangleShape(){};
  RectangleShape(Point2d position = {}, Point2d size = {}, Color fillColor = {},
                 Color outlineColor = {});

  RectangleShape &setOutlineColor(Color color);

  RectangleShape &setFillColor(Color fillColor);

  Shape &setPosition(const Point2d &position);

  RectangleShape &setSize(Point2d size);

  Point2d getPosition() const;

  void draw() const;
};

}; // namespace obstacle

#endif // RECTANGLESHAPE_H_
