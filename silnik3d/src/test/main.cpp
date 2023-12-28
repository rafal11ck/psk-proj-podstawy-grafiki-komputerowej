#include "engine.hpp"
#include <SFML/OpenGL.hpp>
#include <iostream>

Engine &engine{Engine::getInstance()};

int main() {

  engine.setLoopFunction([]() {
    glClearColor(0.0, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  });

  engine.loop();
}
