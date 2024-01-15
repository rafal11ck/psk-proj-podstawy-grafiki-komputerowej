
/**
 *@file
 *@brief Test setting texture.
 **/

/**
 *@file
 *@brief Shape example.
 */

#define TRACE
#include "log.hpp"

#include "engine.hpp"
#include "shape.hpp"
#include <vector>

Engine &engine{Engine::getInstance()};

std::vector<Vertex> verticies{
    {glm::vec3{0.5f, 0.5f, 0.0f}},   // top right
    {glm::vec3{0.5f, -0.5f, 0.0f}},  // bottom right
    {glm::vec3{-0.5f, -0.5f, 0.0f}}, // bottom left
    {glm::vec3{-0.5f, 0.5f, 0.0f}}   // top left
};

std::vector<GLuint> indicies{0, 1, 3, 1, 2, 3};

int main() {
  engine.setMaxFps(1);

  Shape *rectangle = new Shape{verticies, indicies};

  // move it so it won't be clipped.
  rectangle->setPosition(0, 0, -1);

  engine.addDrawable(rectangle);

  engine.loop();

  delete rectangle;
}
