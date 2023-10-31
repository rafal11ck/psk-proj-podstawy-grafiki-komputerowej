#include "character.hpp"
#include "engine.hpp"
#include <iostream>

Character character{"character"};

int main() {
  Engine &eng =
      Engine::getInstance().setWindowTitle("dev").setMaxFps(60).buildWindow();

  eng.loop();
}
