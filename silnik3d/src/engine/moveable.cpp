#include "moveable.hpp"

void Movable::setPosition(GLfloat x, GLfloat y, GLfloat z) {
  setPosition({x, y, z});
};

void Movable::setPosition(glm::vec3 position) { m_position = position; };

glm::vec3 Movable::getPosition() const { return m_position; };
