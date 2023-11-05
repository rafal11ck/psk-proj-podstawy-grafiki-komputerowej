#ifndef FIDGETSPINNER_HPP_
#define FIDGETSPINNER_HPP_

#include "animatedSpriteSheet.hpp"
#include "point2d.hpp"
#include <string_view>

class FidgetSpinner : public AnimatedSpriteSheet {

public:
  FidgetSpinner(std::string_view path);

  virtual void animate() override;

  Point2d getCenterPoint() const;

  void addRotationSpeed(float speed);

  void setRotationResistance(float speed);

private:
  float m_rotationResistance{0.1};
  float m_rotationspeed{0};
  float m_angle{};
};

#endif // FIDGETSPINNER_HPP_
