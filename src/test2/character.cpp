#include "character.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "engine.hpp"
#include <fstream>
#include <iostream>

#define LOGINFO                                                                \
  std::cerr << "\033[35m" << __FILE_NAME__ << " " << __PRETTY_FUNCTION__       \
            << "\033[0m"

Character::Character(std::string datapath) {
  LOGINFO << " " << datapath << '\n';
  std::fstream info;
  info.open(datapath + "/info.txt");

  std::string spritesheetPath;
  info >> spritesheetPath;
  m_spritesheet.loadFromFile(spritesheetPath);

  m_sprite = new sf::Sprite{};
  m_sprite->setTexture(m_spritesheet);

  Engine::getInstance().add(m_sprite);
}
