
#include "shape.hpp"
#define TRACE
#include "log.hpp"

#include "basicMesh.hpp"
#include "engine.hpp"
#include <vector>

Engine &engine{Engine::getInstance()};

std::vector<Vertex> verticies{
    {glm::vec3{0.2f, 0.2f, 0.0f}},   // top right
    {glm::vec3{0.2f, -0.2f, 0.0f}},  // bottom right
    {glm::vec3{-0.2f, -0.2f, 0.0f}}, // bottom left
    {glm::vec3{-0.2f, 0.2f, 0.0f}}   // top left
};

std::vector<GLuint> indicies{0, 1, 3, 1, 2, 3};

int main() {
  engine.setMaxFps(30);

  Shape *MoveRectangle = new Shape{verticies, indicies};
  // MoveRectangle->rotate(glm::radians(-30.f), {0, 0, 1});

  MoveRectangle->setPosition(0.7, 0.7, 0);
  engine.addDrawable(MoveRectangle);

  Shape *rotateRect = new Shape{verticies, indicies};
  engine.addDrawable(rotateRect);

  rotateRect->setPosition(-0.7, 0.7, 0);

  // make it rotate
  const float angleSpeed{45};
  engine.setLoopFunction([&]() {
    float angle = angleSpeed * engine.getLastFrameDuration().asSeconds();

    rotateRect->rotate(glm::radians(angle), {0, 0, 1});
  });

  engine.loop();

  delete MoveRectangle;
}
