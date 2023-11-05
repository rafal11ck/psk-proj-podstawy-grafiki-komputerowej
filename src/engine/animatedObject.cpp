#include "animatedObject.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "log.hpp"

void AnimatedObject::animate() {
  LOGWARN << "Not overloaded " << this << '\n';
};

void AnimatedObject::setPosition(Point2d pos) {
  GameObject::setPosition(pos);
  sf::Sprite::setPosition(pos.toVector2f());
};

void AnimatedObject::move(Point2d vec) {
  GameObject::move(vec);
  sf::Sprite::move(vec.toVector2f());
  // LOGINFO << GameObject::getPosition() << '\n';
};
