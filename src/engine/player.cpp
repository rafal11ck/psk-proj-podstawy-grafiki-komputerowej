#include "player.hpp"
#include "GameObject.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "engine.hpp"
#include "log.hpp"
#include "point2d.hpp"
#include <bits/ranges_algo.h>

Point2d Player::getMoveVectorOrigin() const {
  Point2d vec{};

  if (m_isMoving[static_cast<int>(MoveDirection::north)])
    vec += {0, -1};
  if (m_isMoving[static_cast<int>(MoveDirection::east)])
    vec += {1, 0};
  if (m_isMoving[static_cast<int>(MoveDirection::south)])
    vec += {0, 1};
  if (m_isMoving[static_cast<int>(MoveDirection::west)])
    vec += {-1, 0};
  return vec;
}

void Player::setMovementSpeed(float speed) { m_movementSpeed = speed; }
float Player::getMovementSpeed() const { return m_movementSpeed; };

Point2d Player::getMoveVector() const {
  return getMoveVectorOrigin() * m_movementSpeed *
         Engine::getInstance().getLastFrameDuration().asSeconds();
}

void Player::setIsMoving(MoveDirection direction, bool isMoving) {
  m_isMoving[static_cast<ssize_t>(direction)] = isMoving;
};

bool Player::isMoving() const {
  bool moving{};
  for (auto it : m_isMoving) {
    if (it) {
      moving = true;
      break;
    }
  }
  return moving;
}

void Player::stopMoving() {
  for (auto &it : m_isMoving) {
    it = false;
  }
}

void Player::update() {

  // check if player is moving
  if (isMoving()) {
    Point2d vec = getMoveVector();
    move(vec);
    stopMoving();
  }
};
