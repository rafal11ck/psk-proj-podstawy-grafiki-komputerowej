#ifndef PRIMITIVERENDERER_HPP_
#define PRIMITIVERENDERER_HPP_

#include "SFML/Graphics/Color.hpp"
#include "point2d.hpp"
#include <SFML/Graphics/PrimitiveType.hpp>
#include <vector>

class PrimitiveRenderer {
public:
  static sf::Color s_defaultColor;

public:
  static sf::Color getDefaultColor();

  /**
   * @brief Draw an pixel.
   * @param cord Cordinate at which to draw pixel at. From top left corner.
   * @param color Color of the pixel.
   * */
  static void drawPoint(const Point2d cord, sf::Color color = s_defaultColor);

  static void drawLineIterative(Point2d a, Point2d b,
                                sf::Color color = sf::Color::Green);

  /**
   *@brief
   **/
  static void drawLine(Point2d a, Point2d b,
                       sf::Color color = sf::Color::Green);

  /**
   *@brief Draws a line that goes from point to point
   *@param points Points that line goes through
   *@param color Color
   *@param lastToFirst If true draw line from last point to first
   **/
  static void drawLine(const std::vector<Point2d> &points,
                       sf::Color color = s_defaultColor,
                       bool lastToFirst = false);
};

#endif // PRIMITIVERENDERER_HPP_
