#ifndef PRIMITIVERENDERER_HPP_
#define PRIMITIVERENDERER_HPP_

#include "SFML/Graphics/Color.hpp"
#include "point2d.hpp"
#include <SFML/Graphics/PrimitiveType.hpp>

class PrimitiveRenderer {

public:
  /**
   * @brief Draw an pixel.
   * @param cord Cordinate at which to draw pixel at. From top left corner.
   * @param color Color of the pixel.
   * */
  static void drawPoint(const Point2d cord, sf::Color color = sf::Color::Red);
  static void drawLineIterative(Point2d a, Point2d b);
};

#endif // PRIMITIVERENDERER_HPP_
