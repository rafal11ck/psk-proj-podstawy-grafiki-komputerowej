#include "engine.hpp"

int main() {
  Engine &eng = Engine::getEngine();
  eng.setMaxFrameRate(75);

  eng.loop();
}
