#ifndef PLAYER_H_
#define PLAYER_H_

#include "GameObject.hpp"
#include "SFML/Graphics/Shape.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "animatedObject.hpp"
#include "log.hpp"
#include "point2d.hpp"
#include "updateableObject.hpp"
#include <array>
#include <sys/types.h>

class Player : public AnimatedObject, public UpdateableObject {
public:
  enum class MoveDirection { north, east, south, west, count };

private:
  float m_movementSpeed{50};

  std::array<bool, static_cast<ssize_t>(MoveDirection::count)> m_isMoving{};

  void move(Point2d vec);

public:
  virtual ~Player();
  virtual void setIsMoving(MoveDirection direction);
  virtual void stopMoving(MoveDirection direction);

  void stopMoving();
  bool isMoving() const;
  bool isMoving(MoveDirection direction) const;

  void setMovementSpeed(float speed);
  virtual float getMovementSpeed() const;
  bool isMovingDiagonaly() const;

  Point2d getMoveVectorOrigin() const;
  Point2d getMoveVector() const;

  virtual void update();
};
#endif // PLAYER_H_
