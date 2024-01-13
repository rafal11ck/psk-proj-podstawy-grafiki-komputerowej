#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_

#include "log.hpp"
#include "shader.hpp"

/**
 *@brief Indicates that object is drawable.
 **/
class Drawable {

public:
  virtual void draw(Shader &shader) = 0;

  virtual ~Drawable() { LOGWARN << "Destructor is not overloaded\n"; };
};

#endif // DRAWABLE_HPP_