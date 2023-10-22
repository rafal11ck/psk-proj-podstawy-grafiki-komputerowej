#include "engine.hpp"

int main() {
  Engine &eng =
      Engine::getInstance().setWindowTitle("dev").setMaxFps(1).buildWindow();

  eng.setMaxFps(1);
  eng.loop();
}
