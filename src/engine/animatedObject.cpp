#include "animatedObject.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "log.hpp"

void AnimatedObject::animate() { LOGINFON; };

void AnimatedObject::setPosition(Point2d pos) {
  GameObject::setPosition(pos);
  sf::Sprite::setPosition(pos.toVector2f());
};
