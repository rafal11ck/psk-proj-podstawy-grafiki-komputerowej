#ifndef GAMEOBJECT_HPP_
#define GAMEOBJECT_HPP_

#include "SFML/Graphics/Drawable.hpp"
#include "point2d.hpp"
/**
 * @brief Game object class.
*/
class GameObject {
private:
  /**
   * @brief Position of object on screen.
  */
  Point2d m_position{};

public:
  /**
   * @brief Destructor.
  */
  virtual ~GameObject(){};
  /**
   * @brief Object position setter.
   * @param pos Position to be set.
  */
  virtual void setPosition(Point2d pos);
  /**
   * @brief Object position getter.
  */
  virtual Point2d getPosition() const;
  /**
   * @brief Translates object in space.
   * @param vector 2D vector added to current object position.
  */
  virtual void move(Point2d vector);
};

#endif // GAMEOBJECT_HPP_
