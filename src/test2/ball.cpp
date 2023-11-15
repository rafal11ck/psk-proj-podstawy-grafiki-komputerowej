#include "ball.hpp"
#include "GameObject.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "engine.hpp"
#include "log.hpp"
#include "point2d.hpp"

Ball::Ball(float radius, std::size_t pointCount)
    : sf::CircleShape(radius, pointCount) {}

void Ball::setMovementSpeed(float movementSpeed) {
  m_movementSpeed = movementSpeed;
}

void Ball::setMoveVectorBase(Point2d moveVectorBase) {
  m_moveVectorBase = moveVectorBase;
}

void Ball::move(Point2d vector) {
  GameObject::move(vector);
  sf::CircleShape::move(vector.toVector2f());
}

void Ball::setPositon(Point2d pos) {
  GameObject::setPosition(pos);
  sf::Transformable::setPosition(pos.toVector2f());
}

bool Ball::isDead() const { return m_dead; }

void Ball::update() {
  if (m_timeToLife <= 0) {
    m_dead = true;
    return;
  }
  m_timeToLife -= Engine::getInstance().getLastFrameDuration().asSeconds();

  move(getMoveVector() *
       Engine::getInstance().getLastFrameDuration().asSeconds());
}

Point2d Ball::getMoveVector() { return {m_moveVectorBase * m_movementSpeed}; }
