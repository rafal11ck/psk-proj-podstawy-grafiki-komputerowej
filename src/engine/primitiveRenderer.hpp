#ifndef PRIMITIVERENDERER_HPP_
#define PRIMITIVERENDERER_HPP_

#include "SFML/Graphics/Color.hpp"
#include "drawable.hpp"
#include "point2d.hpp"
#include <SFML/Graphics/PrimitiveType.hpp>
#include <vector>

/**
 *@file
 *@deprecated Bad design. Reinventing wheel.
 **/

namespace obstacle {

/**
 * @deprecated Bad design.
 * */
class PrimitiveRenderer {
public:
  static sf::Color s_defaultColor;

public:
  static sf::Color getDefaultColor();

  static sf::Color getPixelColor(Point2d cord);

  /**
   * @brief Draw an pixel.
   * @param cord Coordinate at which to draw pixel at. From top left corner.
   * @param color Color of the pixel.
   * */
  static void drawPoint(const Point2d cord, sf::Color color = s_defaultColor);

  static void drawLineIterative(Point2d a, Point2d b,
                                sf::Color color = s_defaultColor);

  /**
   *@brief Draw Line
   *@param a Point a of the line.
   *@param b Point b of the line
   *@param color Color of the line.
   **/
  static void drawLine(Point2d a, Point2d b, sf::Color color = s_defaultColor);

  /**
   *@brief Draw a line that goes from point to point
   *@param points Points that line goes through
   *@param color Color
   *@param lastToFirst If true draw line from last point to first
   **/
  static void drawLine(const std::vector<Point2d> &points,
                       sf::Color color = s_defaultColor,
                       bool lastToFirst = false);

  static void drawCircle(Point2d origin, int r,
                         sf::Color color = s_defaultColor);

  static void drawEclipse(Point2d origin, int rx, int ry,
                          sf::Color color = s_defaultColor);

  static void draw(const Drawable &drawable);
};

}; // namespace obstacle

#endif // PRIMITIVERENDERER_HPP_
