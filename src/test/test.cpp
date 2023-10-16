#include "engine.hpp"

int main() {
  Engine &eng = Engine::getEngine();
  eng.setMaxFrameRate(30);

  eng.loop();
}
