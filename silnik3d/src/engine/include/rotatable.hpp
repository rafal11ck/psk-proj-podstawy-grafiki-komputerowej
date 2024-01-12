#ifndef ROTATABLE_HPP_
#define ROTATABLE_HPP_

#include "transformable.hpp"
#include <GL/glew.h>
#include <glm/glm.hpp>

class Rotatable : virtual public Transformable {
private:
  glm::mat4 m_rotationMatrix{1.f};

public:
  virtual void rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
  virtual void rotate(GLfloat angle, glm::vec3 origin);
};

#endif // ROTATABLE_HPP_
