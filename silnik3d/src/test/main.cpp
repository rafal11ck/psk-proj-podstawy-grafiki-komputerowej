#include "rotatable.hpp"
#define TRACE
#include "log.hpp"

#include "basicMesh.hpp"
#include "engine.hpp"
#include "shader.hpp"
#include <iostream>
#include <vector>

Engine &engine{Engine::getInstance()};

std::vector<Vertex> verticies{
    {glm::vec3{0.5f, 0.5f, 0.0f}},   // top right
    {glm::vec3{0.5f, -0.5f, 0.0f}},  // bottom right
    {glm::vec3{-0.5f, -0.5f, 0.0f}}, // bottom left
    {glm::vec3{-0.5f, 0.5f, 0.0f}}   // top left
};

std::vector<GLuint> indicies{0, 1, 3, 1, 2, 3};

Shader shader("vertex.glsl", "fragment.glsl");

int main() {
  engine.setMaxFps(1);

  BasicMesh *rectangle = new BasicMesh{verticies, indicies};

  // engine.addDrawable(rectangle);

  engine.setLoopFunction([&]() {
    LOGINFO << "Invoked custom loop function\n";

    rectangle->draw(shader);
  });

  engine.loop();

  delete rectangle;
}
