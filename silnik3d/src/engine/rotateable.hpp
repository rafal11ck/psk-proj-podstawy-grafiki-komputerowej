#ifndef ROTATEABLE_HPP_
#define ROTATEABLE_HPP_

#include "transformable.hpp"
#include <GL/glew.h>

class Rotatable : virtual public Transformable {
public:
  virtual void rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
  virtual void rotate(GLfloat angle, glm::vec3 origin);
};

#endif // ROTATEABLE_HPP_
