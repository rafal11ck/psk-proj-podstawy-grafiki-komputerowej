#include "point2d.hpp"
#include "SFML/System/Vector2.hpp"
#include "log.hpp"
#include <cmath>
#include <istream>
#include <iterator>
#include <optional>
#include <ostream>

Point2d::Point2d(cordinate_t x, cordinate_t y) : m_x(x), m_y(y){};
Point2d::Point2d(const sf::Vector2f &vector) : m_x{vector.x}, m_y{vector.y} {};
Point2d::Point2d(const sf::Vector2i &vector)
    : m_x{static_cast<cordinate_t>(vector.x)},
      m_y{static_cast<cordinate_t>(vector.y)} {};

Point2d operator+(const Point2d &a, const Point2d &b) {
  return {a.m_x + b.m_x, a.m_y + b.m_y};
}

Point2d &operator+=(Point2d &a, const Point2d &b) {
  a = a + b;
  return a;
}

Point2d operator-(const Point2d &a, const Point2d &b) {
  return operator+(a, -1 * b);
}

Point2d operator*(const Point2d &a, float b) {
  return {a.getX() * b, a.getY() * b};
};

Point2d operator*(float b, const Point2d &a) { return operator*(a, b); }

std::ostream &operator<<(std::ostream &os, const Point2d &point) {
  os << "Point2d(" << point.m_x << ", " << point.m_y << ")";
  return os;
}

std::istream &operator>>(std::istream &is, Point2d &point) {
  is >> point.m_x;
  is >> point.m_y;
  return is;
}

bool operator==(const Point2d &a, const Point2d &b) {
  return a.getX() == b.getX() && a.getY() == b.getY();
}

bool operator!=(const Point2d &a, const Point2d &b) {
  return !operator==(a, b);
}

Point2d::cordinate_t Point2d::getX() const { return m_x; };
Point2d::cordinate_t Point2d::getY() const { return m_y; };

void Point2d::setX(cordinate_t x) { m_x = x; };
void Point2d::setY(cordinate_t y) { m_y = y; };
/**
 * @brief Swaps co-ordinates with another point.
 * @param b Point to swap co-ordinates with.
 */
void Point2d::swap(Point2d &b) {
  std::swap(m_x, b.m_x);
  std::swap(m_y, b.m_y);
}

sf::Vector2f Point2d::toVector2f() const {
  return {static_cast<float>(m_x), static_cast<float>(m_y)};
}

Point2d::cordinate_t Point2d::length() const {
  return std::sqrt((m_x * m_x) + (m_y * m_y));
  return length();
}

Point2d::cordinate_t Point2d::distanceTo(const Point2d &point) const {
  return (*this - point).length();
};
