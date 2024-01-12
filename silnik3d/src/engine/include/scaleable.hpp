#ifndef SCALEABLE_HPP_
#define SCALEABLE_HPP_

#include "transformable.hpp"
#include <GL/glew.h>
#include <glm/glm.hpp>

class Scalable : virtual public Transformable {
  glm::vec3 m_scale;

public:
  void setScale(GLfloat x, GLfloat y, GLfloat z);
  void setScale(glm::vec3 scale);
};

#endif // SCALEABLE_HPP_
