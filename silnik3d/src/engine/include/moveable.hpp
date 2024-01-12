#ifndef MOVEABLE_HPP_
#define MOVEABLE_HPP_

#include "transformable.hpp"
#include <GL/glew.h>
#include <glm/glm.hpp>

class Movable : virtual public Transformable {
private:
  glm::vec3 m_position{};

public:
  void setPosition(GLfloat x, GLfloat y, GLfloat z);
  void setPosition(glm::vec3 position);

  glm::vec3 getPosition() const;

  virtual ~Movable();
};

#endif // MOVEABLE_HPP_
