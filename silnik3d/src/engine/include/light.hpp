#ifndef LIGHT_HPP_
#define LIGHT_HPP_

#include "cube.hpp"
#include "moveable.hpp"
#include "shader.hpp"
#include <glm/glm.hpp>

class Light : public Movable {
private:
  glm::vec3 ambient{0};
  glm::vec3 diffuse{0};
  glm::vec3 specular{0};

public:
  Light();
  ~Light();

  void setAmbient(glm::vec3 ambient);
  void setDiffuse(glm::vec3 diffuse);
  void setSpecular(glm::vec3 specular);
  void setAmbient(GLfloat r, GLfloat g, GLfloat b);
  void setDiffuse(GLfloat r, GLfloat g, GLfloat b);
  void setSpecular(GLfloat r, GLfloat g, GLfloat b);

  glm::vec3 getAmbient() const;
  glm::vec3 getDiffuse() const;
  glm::vec3 getSpecular() const;

  /**
   *@brief Sets shader uniforms to data from this light
   **/
  void update(Shader &shader, int index) const;
};

#endif // LIGHT_HPP_
