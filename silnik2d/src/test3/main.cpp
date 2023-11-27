#include "SFML/Graphics/Color.hpp"
#include "animatedSpriteSheet.hpp"
#include "engine.hpp"
#include <iostream>

namespace G {
std::string basePath = "resources/";
}; // namespace G

AnimatedSpriteSheet animation(G::basePath + "animation");

int main() {
  Engine::getInstance().setMaxFps(3).setResolution({1000, 1000}).buildWindow();

  animation.setPosition({300, 300});
  animation.setColor(sf::Color::Cyan);

  Engine::getInstance().add(&animation);

  Engine::getInstance().loop();
}
