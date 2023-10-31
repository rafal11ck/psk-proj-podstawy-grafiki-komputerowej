#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "point2d.hpp"
#include <fstream>
#include <string>

class Character {
public:
  sf::Sprite *m_sprite{};
  sf::Texture m_spritesheet{};

  Point2d m_postion{};
  float m_movementSpeed{50};
  std::pair<int, int> currentSprite{};
  std::pair<int, int> spriteSize{};

public:
  ~Character(){};
  Character(std::string datapath);

  void move(Point2d distance){};
  void setSpriteSheetFile(std::string){};
};

#endif // CHARACTER_H_
