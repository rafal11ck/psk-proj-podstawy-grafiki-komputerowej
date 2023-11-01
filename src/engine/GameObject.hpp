#ifndef GAMEOBJECT_HPP_
#define GAMEOBJECT_HPP_

#include "SFML/Graphics/Drawable.hpp"
#include "point2d.hpp"

class GameObject {
private:
  Point2d m_position{};

public:
  virtual ~GameObject(){};

  virtual void setPosition(Point2d pos);
  virtual Point2d getPosition() const;
  virtual void move(Point2d vector);
};

#endif // GAMEOBJECT_HPP_
