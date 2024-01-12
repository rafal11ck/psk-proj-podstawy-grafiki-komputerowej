#include "shape.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#define TRACE
#include "log.hpp"

glm::mat4 Shape::getModelMatrix() {
  LOGTRACEN;
  return glm::translate(glm::mat4(1.0f), getPosition());
};
