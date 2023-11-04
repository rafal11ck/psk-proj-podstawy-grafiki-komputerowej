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
/**
 * @brief Player class.
*/
class Player : public AnimatedObject, public UpdateableObject {
public:
  /**
   * @brief Directions of movement.
  */
  enum class MoveDirection { north, east, south, west, count };

private:
  /**
   * @brief Player movement speed.
  */
  float m_movementSpeed{50};
  /**
   * @brief Array with player's current movement direction.
  */
  std::array<bool, static_cast<ssize_t>(MoveDirection::count)> m_isMoving{};
  /**
   * @brief Moves player on screen.
   * @param vec Vector by which player is moved.
  */
  void move(Point2d vec);

public:
  /**
   * @brief Destructor.
  */
  virtual ~Player();
  /**
   * @brief 
   * @param direction
  */
  virtual void setIsMoving(MoveDirection direction);
  /**
   * @brief
   * @param direction
  */
  virtual void stopMoving(MoveDirection direction);

  /**
   * @brief Stops player from moving.
  */
  void stopMoving();
  /**
   * @brief Checks if player is moving.
  */
  bool isMoving() const;
  /**
   * @brief Checks if player is moving in a specific direction.
   * @param direction Direction checked.
  */
  bool isMoving(MoveDirection direction) const;

  /**
   * @brief Player movement speed setter.
  */
  void setMovementSpeed(float speed);
  /**
   * @brief Player movement speed getter.
  */
  virtual float getMovementSpeed() const;
  /**
   * @brief Checks if player is moving diagonally.
  */
  bool isMovingDiagonaly() const;

  /**
   * @brief Returns a 2D vector containing information on which cardinal directions the player is moving.
  */
  Point2d getMoveVectorOrigin() const;
  /**
   * @brief Returns the player's movement vector multiplied by speed.
  */
  Point2d getMoveVector() const;

  /**
   * @brief update???????????
  */
  virtual void update();
};
#endif // PLAYER_H_
