#ifndef POINT2D_HPP_
#define POINT2D_HPP_

#include "SFML/System/Vector2.hpp"
#include <ostream>
/**
 * @brief Class containing 2D point co-ordinates.
 */
class Point2d {
public:
  using cordinate_t = float;

private:
  /**
   * @brief X co-ordinate of the point.
   */
  cordinate_t m_x;
  /**
   * @brief Y co-ordinate of the point.
   */
  cordinate_t m_y;

public:
  /**
   * @brief Constructor.
   * @param x X co-ordinate of point.
   * @param y Y co-ordinate of point.
   */
  Point2d(cordinate_t x = 0, cordinate_t y = 0);
  /**
   * @brief Copy constructor.
   * @param point Instance of class Point2d.
   */
  Point2d(const Point2d &point) = default;
  /**
   * @brief Constructor.
   * @param vector 2D vector.
   */
  explicit Point2d(const sf::Vector2f &vector);

  explicit Point2d(const sf::Vector2i &vector);

  friend Point2d operator+(const Point2d &a, const Point2d &b);
  friend Point2d &operator+=(Point2d &a, const Point2d &b);

  friend Point2d operator-(const Point2d &a, const Point2d &b);

  friend bool operator==(const Point2d &a, const Point2d &b);
  friend bool operator!=(const Point2d &a, const Point2d &b);

  friend Point2d operator*(const Point2d &a, float b);
  friend Point2d operator*(float b, const Point2d &a);

  friend std::ostream &operator<<(std::ostream &os, const Point2d &point);

  friend std::istream &operator>>(std::istream &is, Point2d &point);

  /**
   * @brief X co-ordinate getter.
   */
  cordinate_t getX() const;
  /**
   * @brief Y co-ordinate getter.
   */
  cordinate_t getY() const;
  /**
   * @brief X co-ordinate setter.
   */
  void setX(cordinate_t x);
  /**
   * @brief Y co-ordinate setter.
   */
  void setY(cordinate_t y);

  void swap(Point2d &b);
  /**
   * @brief Convert to Vector2f.
   */
  sf::Vector2f toVector2f() const;
  /**
   * @brief Get length of vector.
  */
  cordinate_t length() const;
  /**
   * @brief Get distance between two points.
   * @param point Point to which distance is calculated.
  */
  cordinate_t distanceTo(const Point2d &point) const;
};

#endif // POINT2D_HPP_
