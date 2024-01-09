#ifndef LIGHT_HPP_
#define LIGHT_HPP_

#include "movable.hpp"
#include "shader.hpp"
#include "shape.hpp"
#include "updateable.hpp"

class Light : public Updatable, public Movable {
private:
  glm::vec3 m_ambient;
  glm::vec3 m_diffuse;
  glm::vec3 m_specular;

public:
  Light();

  void setAmbient(glm::vec3 ambient);
  void setDiffuse(glm::vec3 diffuse);
  void setSpecular(glm::vec3 specular);
  void setAmbient(GLfloat r, GLfloat g, GLfloat b);
  void setDiffuse(GLfloat r, GLfloat g, GLfloat b);
  void setSpecular(GLfloat r, GLfloat g, GLfloat b);

  glm::vec3 getAmbient();
  glm::vec3 getDiffuse();
  glm::vec3 getSpecular();

  void update(Shader &shader, int index);
};
#endif // LIGHT_HPP_
