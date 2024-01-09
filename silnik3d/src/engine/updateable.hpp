#ifndef UPDATEABLE_HPP_
#define UPDATEABLE_HPP_

#include "shader.hpp"

class Updatable {
public:
  virtual void update(Shader &shader) = 0;
  virtual void update(Shader &shader, int index) = 0;
};

#endif // UPDATEABLE_HPP_
