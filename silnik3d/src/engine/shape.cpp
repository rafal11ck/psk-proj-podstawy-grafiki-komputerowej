
#define TRACE
#include "log.hpp"

#include "basicMesh.hpp"
#include "shader.hpp"
#include "shape.hpp"
#include <glm/ext/matrix_transform.hpp>

Shape::Shape(verticies_t verticies, indicies_t indicies)
    : BasicMesh(verticies, indicies) {
  LOGTRACEN;
}

glm::mat4 Shape::getModelMatrix() {
  LOGTRACEN;

  glm::mat4 model{1};

  model = glm::translate(model, getPosition());

  model = model * getRotationMatrix();

  return model;
};

void Shape::draw(Shader &shader) {
  shader.use();
  shader.setMat4("model", getModelMatrix());
  BasicMesh::draw(shader);
}

Shape::~Shape() { LOGINFO << "Destroying\n"; }
