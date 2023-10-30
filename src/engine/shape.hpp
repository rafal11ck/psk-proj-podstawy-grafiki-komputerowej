#ifndef SHAPE_H_
#define SHAPE_H_

/**
 * @brief abstract class
 */

#include "drawable.hpp"
#include "point2d.hpp"

class Shape : public Drawable {

public:
  virtual ~Shape(){};

  virtual Shape &setPosition(const Point2d &point) = 0;
  virtual Point2d getPosition() const = 0;
};

#endif // SHAPE_H_
