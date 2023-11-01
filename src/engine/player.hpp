#ifndef PLAYER_H_
#define PLAYER_H_

#include "GameObject.hpp"
#include "SFML/Graphics/Shape.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "log.hpp"
#include "point2d.hpp"
#include "updateableObject.hpp"
#include <array>
#include <sys/types.h>

class Player : public GameObject, public UpdateableObject, public sf::Sprite {
public:
  enum class MoveDirection { north, east, south, west, count };

private:
  float m_movementSpeed{50};

  std::array<bool, static_cast<ssize_t>(MoveDirection::count)> m_isMoving{};

  void move(Point2d vec) {
    GameObject::move(vec);
    sf::Sprite::move(getMoveVector().toVector2f());
    // LOGINFO << GameObject::getPosition() << '\n';
  };

public:
  void setIsMoving(MoveDirection direction, bool isMoving = true);
  bool isMoving() const;
  void stopMoving();

  void setMovementSpeed(float speed);
  float getMovementSpeed() const;

  Point2d getMoveVectorOrigin() const;
  Point2d getMoveVector() const;

  void update();
};
#endif // PLAYER_H_
