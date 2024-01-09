#ifndef SCALEABLE_HPP_
#define SCALEABLE_HPP_

#include "transformable.hpp"
#include <GL/glew.h>

class Scalable : virtual public Transformable {
public:
  virtual void scale(GLfloat x, GLfloat y, GLfloat z);
  virtual void scale(glm::vec3 scale);
};

#endif // SCALEABLE_HPP_
