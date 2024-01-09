#ifndef MOVABLE_HPP_
#define MOVABLE_HPP_

#include "transformable.hpp"
#include <GL/glew.h>

class Movable : virtual public Transformable {
protected:
  glm::vec3 m_position{};

public:
  glm::vec3 getPosition();

  virtual void move(GLfloat x, GLfloat y, GLfloat z);
  virtual void move(glm::vec3 translation);
};

#endif // MOVABLE_HPP_
