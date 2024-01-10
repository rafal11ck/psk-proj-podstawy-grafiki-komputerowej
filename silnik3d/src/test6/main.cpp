#include "cube.hpp"
#include "engine.hpp"
#include <iostream>

Engine &engine{Engine::getInstance()};

int main() {

  Cube *cube = new Cube{};
  std::cout << "Cube intialized\n";
  engine.addShape(cube);

  cube->initialize();

  engine.loop();
}
