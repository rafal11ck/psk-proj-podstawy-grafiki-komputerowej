
#include "gamePlayer.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "animatedObject.hpp"
#include "engine.hpp"
#include "log.hpp"
#include "player.hpp"
#include "point2d.hpp"
#include <cmath>
#include <sys/types.h>

// #define NOTRACE

GamePlayer::GamePlayer() {
  LOGINFON;
  loadFromFile(
      std::string(s_spriteSheetPath),
      sf::IntRect{0, 0, 4 * 300, static_cast<int>(AnimationType::count) * 300});
  setTexture(*this);
  setTextureRect(getCurrentAnimationFrameSpriteRectangle());
}

sf::IntRect GamePlayer::getCurrentAnimationFrameSpriteRectangle() const {
  sf::IntRect result{m_aninmationFrameIndicator * 300,
                     getRowOfAnimation() * 300, 300, 300};
  // LOGINFO << result.top << '\t' << result.left << '\n';
  return result;
}

void GamePlayer::animate() {
  m_animationTimer += Engine::getInstance().getLastFrameDuration().asSeconds();
  // wait for next frame change
  if (m_animationTimer < m_animationFrameDuration)
    return;
  // reset timer
  m_animationTimer = 0;
  // do frame changing
  nextAnimationFrame();
}

void GamePlayer::update() {
  Player::update();

  // Handle animation update
  AnimationType animation = AnimationType::standing;

  if (isMoving()) {
    // if is moving diagonally
    if (isMovingDiagonaly()) {
      animation = AnimationType::moveSpecial;
    } else {
      // check if is moving in any single direction
      for (int i{}; i < static_cast<int>(MoveDirection::count); ++i) {
        MoveDirection moveDir{static_cast<MoveDirection>(i)};
        if (isMoving(moveDir)) {
          animation = getAnimationTypeOf(moveDir);
          break;
        }
      }
    }
  }

  setAnimationType(animation);
}

int GamePlayer::getFrameCountOfAnimation(AnimationType type) const {
  switch (type) {
  case AnimationType::standing:
    return 4;
  case AnimationType::moveNorth:
    return 4;
  case AnimationType::moveEast:
    return 4;
  case AnimationType::moveSouth:
    return 4;
  case AnimationType::moveWest:
    return 4;
  case AnimationType::moveSpecial:
    return 4;
  default:
    LOGWARN << "Animation type not handled!\n";
    return 0;
    break;
  }
}

void GamePlayer::setAnimationType(GamePlayer::AnimationType type) {
  // Do no reset current animation if new is same.
  if (type == m_animationType)
    return;
  m_animationType = type;
  m_aninmationFrameIndicator = 0;
  m_animationTimer = 0;
  nextAnimationFrame();
};

GamePlayer::AnimationType
GamePlayer::getAnimationTypeOf(MoveDirection moveDirection) const {
  switch (moveDirection) {
  case Player::MoveDirection::north:
    return AnimationType::moveNorth;
  case Player::MoveDirection::east:
    return AnimationType::moveEast;
  case Player::MoveDirection::south:
    return AnimationType::moveSouth;
  case Player::MoveDirection::west:
    return AnimationType::moveWest;
  default:
    LOGWARN << "UNHANDLED\n";
    break;
  }
  return AnimationType::standing;
}

void GamePlayer::nextAnimationFrame() {
  ++m_aninmationFrameIndicator;
  m_aninmationFrameIndicator %= getFrameCountOfAnimation(m_animationType);
  updateTextureRect();
  // LOGINFO << "Frame: " << m_aninmationFrameIndicator
  //         << " Type: " << static_cast<int>(m_animationType) << '\n';
};

void GamePlayer::updateTextureRect() {
  this->setTextureRect(getCurrentAnimationFrameSpriteRectangle());
}

int GamePlayer::getRowOfAnimation() const {
  switch (m_animationType) {
  case AnimationType::standing:
    return 0;
  case AnimationType::moveNorth:
    return 1;
  case AnimationType::moveEast:
    return 2;
  case AnimationType::moveSouth:
    return 3;
  case AnimationType::moveWest:
    return 4;
  case AnimationType::moveSpecial:
    return 5;
  default:
    LOGWARN << "not handled\n";
    return 0;
  };
};
