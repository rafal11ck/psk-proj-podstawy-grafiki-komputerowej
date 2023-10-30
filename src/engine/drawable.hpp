#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include "SFML/Graphics/Color.hpp"
class Drawable {

public:
  using Color = sf::Color;

  virtual ~Drawable();

  /**
   *@brief draw */
  virtual void draw() const = 0;
};

#endif // DRAWABLE_H_
