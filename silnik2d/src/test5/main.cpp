

#include "engine.hpp"
#include <iostream>

int main() {
  Engine &eng = Engine::getInstance().setWindowTitle("dev").buildWindow();

  eng.loop();
}
