#ifndef POINT2D_HPP_
#define POINT2D_HPP_

#include "SFML/System/Vector2.hpp"
#include <ostream>

class Point2d {
public:
  using cordinate_t = float;

private:
  cordinate_t m_x;
  cordinate_t m_y;

public:
  Point2d(cordinate_t x = 0, cordinate_t y = 0);
  Point2d(const Point2d &point) = default;

  explicit Point2d(const sf::Vector2f &vector);

  friend Point2d operator+(const Point2d &a, const Point2d &b);
  friend Point2d &operator+=(Point2d &a, const Point2d &b);

  friend Point2d operator*(const Point2d &a, float b);

  friend std::ostream &operator<<(std::ostream &os, const Point2d &point);

  cordinate_t getX() const;
  cordinate_t getY() const;

  void setX(cordinate_t x);
  void setY(cordinate_t y);

  void swap(Point2d &b);

  sf::Vector2f toVector2f() const;
};

#endif // POINT2D_HPP_
