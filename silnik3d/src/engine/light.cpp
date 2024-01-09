
#include "light.hpp"
#include "engine.hpp"

Light::Light() {
  m_diffuse = glm::vec3(0.5f);
  m_ambient = glm::vec3(0.2f);
  m_specular = glm::vec3(1.0f);
}

void Light::setAmbient(glm::vec3 ambient) { this->m_ambient = ambient; }

void Light::setDiffuse(glm::vec3 diffuse) { this->m_diffuse = diffuse; }

void Light::setSpecular(glm::vec3 specular) { this->m_specular = specular; }

void Light::setAmbient(GLfloat r, GLfloat g, GLfloat b) {
  this->m_ambient = glm::vec3(r, g, b);
}

void Light::setDiffuse(GLfloat r, GLfloat g, GLfloat b) {
  this->m_diffuse = glm::vec3(r, g, b);
}

void Light::setSpecular(GLfloat r, GLfloat g, GLfloat b) {
  this->m_specular = glm::vec3(r, g, b);
}

glm::vec3 Light::getAmbient() { return this->m_ambient; }

glm::vec3 Light::getDiffuse() { return this->m_diffuse; }

glm::vec3 Light::getSpecular() { return this->m_specular; }

void Light::update(Shader &shader, int index) {
  if (index >= 8 || index < 0) {
    std::cout << "SHADER ERROR" << std::endl;
    std::cout
        << "Light index out of range. This value should be between 0 and 7."
        << std::endl;
    return;
  }

  std::string lightName = "light[" + std::to_string(index) + "]";

  shader.use();
  shader.setVec3(lightName + ".position", m_position);
  shader.setVec3(lightName + ".ambient", m_ambient);
  shader.setVec3(lightName + ".diffuse", m_diffuse);
  shader.setVec3(lightName + ".specular", m_specular);
}
