#include "animatedSpriteSheet.hpp"
#include "engine.hpp"
#include "log.hpp"
#include <iostream>

namespace G {
Engine &eng{Engine::getInstance()};
std::string basePath = "resources/";
}; // namespace G

int main() {
  G::eng.getInstance().setMaxFps(75).setResolution({1000, 1000}).buildWindow();

  AnimatedSpriteSheet animation(G::basePath + "animation");

  G::eng.loop();
}
