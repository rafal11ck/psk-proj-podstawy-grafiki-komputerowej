#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_

#include "shader.hpp"

class Drawable {
public:
  virtual void draw(Shader &shader) = 0;
};

#endif // DRAWABLE_HPP_
