#include "bush.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "engine.hpp"
#include "log.hpp"
#include <system_error>

Bush::~Bush(){};

Bush::Bush() {
  LOGINFON;
  loadFromFile(std::string(s_spriteSheetPath), sf::IntRect{0, 0, 300, 150});
  setTexture(*this);
  setTextureRect(getCurrentSpriteRectangle(0));
}

void Bush::animate() {
  m_animationTimer += Engine::getInstance().getLastFrameDuration().asSeconds();
  if (m_animationTimer > m_animationFrameDuration) {
    nextSprite();
    m_animationTimer = 0;
  }
}

void Bush::nextSprite() {
  ++m_aninmationFrameIndicator;
  m_aninmationFrameIndicator %= 2;
  this->setTextureRect(getCurrentSpriteRectangle(m_aninmationFrameIndicator));
}

sf::IntRect Bush::getCurrentSpriteRectangle(int frameNumber) {
  return sf::IntRect{frameNumber * 150, 0, 150, 150};
}
