#ifndef DRAWABLE_H_
#define DRAWABLE_H_

/**
 * @brief abstract class for drawables
 */

#include "SFML/Graphics/Color.hpp"
#include "point2d.hpp"
class Drawable {

public:
  virtual ~Drawable(){};
  using Color = sf::Color;

  /**
   *@brief draw */
  virtual void draw() const = 0;

  virtual Drawable &setPosition(const Point2d &point) = 0;
  virtual Point2d getPosition() const = 0;
};

#endif // DRAWABLE_H_
