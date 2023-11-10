#ifndef BALL_HPP_
#define BALL_HPP_

#include "GameObject.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "animatedObject.hpp"
#include "point2d.hpp"
#include "updateableObject.hpp"

class Ball : public GameObject,
             public sf::CircleShape,
             public UpdateableObject {
public:
  Ball(float radius = 10, std::size_t pointCount = 30);

  void setMovementSpeed(float movementSpeed);
  void setMoveVectorBase(Point2d moveVectorOrigin);

  virtual void update();
  virtual void move(Point2d vector);
  virtual void setPositon(Point2d pos);

  bool wasRemovedFromEngine() const;

private:
  Point2d getMoveVector();

private:
  float m_movementSpeed{30};
  Point2d m_moveVectorBase;
  float m_timeToLife{15};
  bool m_removedFromEngine{false};
};

#endif // BALL_HPP_
