#include "rotateable.hpp"
#include <glm/ext/matrix_transform.hpp>

void Rotatable::rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) {
  m_model = glm::rotate(m_model, angle, glm::vec3(x, y, z));
}

void Rotatable::rotate(GLfloat angle, glm::vec3 origin) {
  m_model = glm::rotate(m_model, angle, origin);
}
