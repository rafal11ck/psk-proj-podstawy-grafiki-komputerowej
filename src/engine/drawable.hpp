#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include "SFML/Graphics/Color.hpp"

/**
 *@file
 *@deprecated Bad design. Reinventing wheel.
 **/

namespace obstacle {

class Drawable {

public:
  using Color = sf::Color;

  virtual ~Drawable(){};

  /**
   *@brief draw */
  virtual void draw() const = 0;
};

};     // namespace obstacle
#endif // DRAWABLE_H_
