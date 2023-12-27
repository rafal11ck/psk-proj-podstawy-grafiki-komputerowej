#include "engine.hpp"
#include <iostream>

int main() {
  Engine engine{};
  engine.buildWindow().loop();
}
