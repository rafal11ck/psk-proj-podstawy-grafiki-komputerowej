
#include "SFML/Graphics/Sprite.hpp"
#include "engine.hpp"
#include <iostream>

sf::Sprite *sprite = new sf::Sprite{};

int main() {
  Engine &eng = Engine::getInstance().setWindowTitle("dev").buildWindow();

  sf::Texture texture;

  // texture file paths are relative to executable file, not source file.
  if (!texture.loadFromFile("textureFile.png", sf::IntRect(0, 0, 200, 200))) {
    std::cout << "Could not find texture file";
  }

  sprite->setTexture(texture);
  eng.add(sprite);

  eng.loop();
}
