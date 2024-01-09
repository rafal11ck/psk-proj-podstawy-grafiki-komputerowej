#include "scaleable.hpp"

#include <glm/ext/matrix_transform.hpp>

void Scalable::scale(GLfloat x, GLfloat y, GLfloat z) {
  m_model = glm::scale(m_model, glm::vec3(x, y, z));
}

void Scalable::scale(glm::vec3 scale) { m_model = glm::scale(m_model, scale); }
