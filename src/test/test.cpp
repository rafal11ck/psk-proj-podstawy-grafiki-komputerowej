#include "engine.hpp"

int main() {
  Engine &eng = Engine::getEngine();
  eng.setMaxFrameRate(60);

  eng.loop();
}
