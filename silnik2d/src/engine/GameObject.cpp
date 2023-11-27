#include "GameObject.hpp"
#include "log.hpp"
#include "point2d.hpp"

void GameObject::setPosition(Point2d pos) { m_position = pos; }

Point2d GameObject::getPosition() const { return m_position; }

void GameObject::move(Point2d vector) {
  m_position += vector;
  // LOGINFO << vector << '\t' << m_position << '\n';
}
