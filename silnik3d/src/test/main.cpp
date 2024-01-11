#include "basicMesh.hpp"
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

  BasicMesh rectangle{verticies, indicies};

  engine.setLoopFunction([&]() {
    glClearColor(0.0, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    rectangle.drawElements(shader);
  });

  engine.loop();
}
