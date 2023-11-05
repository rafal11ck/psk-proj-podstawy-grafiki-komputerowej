#include "animatedSpriteSheet.hpp"
#include "engine.hpp"
#include "log.hpp"
#include <iostream>

namespace G {
std::string basePath = "resources/";
}; // namespace G

AnimatedSpriteSheet animation(G::basePath + "animation");

int main() {
  Engine::getInstance().setMaxFps(75).setResolution({1000, 1000}).buildWindow();

  Engine::getInstance().add(&animation);

  Engine::getInstance().loop();
}
