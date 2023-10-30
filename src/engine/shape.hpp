#ifndef SHAPE_H_
#define SHAPE_H_

#include "drawable.hpp"
#include "point2d.hpp"

/**
 *@file
 *@deprecated Bad design. Reinventing wheel.
 **/

namespace obstacle {
/**
 * @brief abstract class
 */
class Shape : public Drawable {

public:
  virtual ~Shape(){};

  virtual Shape &setPosition(const Point2d &point) = 0;
  virtual Point2d getPosition() const = 0;
};

};     // namespace obstacle
#endif // SHAPE_H_
