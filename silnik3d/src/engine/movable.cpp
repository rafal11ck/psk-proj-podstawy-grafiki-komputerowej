#include "movable.hpp"

#include <glm/ext/matrix_transform.hpp>

glm::vec3 Movable::getPosition() { return m_position; }

void Movable::move(GLfloat x, GLfloat y, GLfloat z) {
  m_model = glm::translate(m_model, glm::vec3(x, y, z));
  m_position += glm::vec3(x, y, z);
}

void Movable::move(glm::vec3 translation) {
  m_model = glm::translate(m_model, translation);
  m_position += translation;
}
