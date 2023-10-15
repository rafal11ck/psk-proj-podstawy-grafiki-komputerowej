#ifndef POINT2D_HPP_
#define POINT2D_HPP_

class Point2d {
public:
  using cordinate_t = long long;

private:
  cordinate_t m_x;
  cordinate_t m_y;

public:
  Point2d(cordinate_t x = 0, cordinate_t y = 0);

  friend Point2d operator+(const Point2d &a, const Point2d &b);

  cordinate_t getX() const;
  cordinate_t getY() const;

  void setX(cordinate_t x);
  void setY(cordinate_t y);

  void swap(Point2d &b);
};

#endif // POINT2D_HPP_
