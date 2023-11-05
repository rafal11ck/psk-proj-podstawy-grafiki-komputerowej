#include "fidgetSpinner.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "animatedSpriteSheet.hpp"
#include "engine.hpp"
#include "log.hpp"
#include "point2d.hpp"

FidgetSpinner::FidgetSpinner(std::string_view path)
    : AnimatedSpriteSheet(path) {
  LOGINFON;

  Point2d offset(getSize().x / 2.f + 0.5f, getSize().y / 2.f + 0.5f);
  setOrigin(offset.toVector2f());
};

void FidgetSpinner::animate() {
  m_angle += m_rotationspeed *
             Engine::getInstance().getLastFrameDuration().asSeconds();
  setRotation(m_angle);

  if (m_rotationspeed > 0) {
    m_rotationspeed -= m_rotationResistance + m_rotationspeed / 500;
    if (m_rotationspeed < 0)
      m_rotationspeed = 0;
  }
}

Point2d FidgetSpinner::getCenterPoint() const {
  Point2d point{getCurrentAnimationFrameData().m_position +
                getCurrentAnimationFrameData().m_size * 0.5};

  return point;
}

void FidgetSpinner::addRotationSpeed(float speed) { m_rotationspeed += speed; }

void FidgetSpinner::setRotationResistance(float speed) {
  m_rotationResistance = speed;
}
