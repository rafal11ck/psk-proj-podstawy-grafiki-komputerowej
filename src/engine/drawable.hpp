#ifndef DRAWABLE_H_
#define DRAWABLE_H_

/**
 * @brief abstract class for drawables
 */

#include "SFML/Graphics/Color.hpp"
class Drawable {

public:
  using Color = sf::Color;

  /**
   *@brief draw */
  virtual void draw() const = 0;
};

#endif // DRAWABLE_H_
