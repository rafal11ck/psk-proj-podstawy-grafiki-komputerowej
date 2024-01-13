#include "shape.hpp"
#include "basicMesh.hpp"
#include "shader.hpp"
#include <glm/ext/matrix_transform.hpp>
#define TRACE
#include "log.hpp"

Shape::Shape(verticies_t verticies, indicies_t indicies)
    : BasicMesh(verticies, indicies) {}

glm::mat4 Shape::getModelMatrix() {
  LOGTRACEN;

  glm::mat4 model(1);
  // move the object
  model = glm::translate(model, getPosition());

  return model;
};

void Shape::draw(Shader &shader) {
  shader.use();
  shader.setMat4("model", getModelMatrix());
  BasicMesh::draw(shader);
}

Shape::~Shape() { LOGINFO << "Destroying\n"; }
