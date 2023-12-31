#ifndef ANIMATEDOBJECT_H_
#define ANIMATEDOBJECT_H_

#include "GameObject.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "point2d.hpp"
#include <vector>

/**
 * @brief Animated object class.
 * */
class AnimatedObject : public GameObject,
                       public sf::Sprite,
                       public sf::Texture {

public:
  /**
   * @brief Destructor.
   */
  virtual ~AnimatedObject(){};
  /**
   * @brief Object position setter.
   * @param pos Position to be set.
   */
  virtual void setPosition(Point2d pos);
  /**
   * @brief Animates object.
   */
  virtual void animate();

  virtual void move(Point2d vec);

private:
};

#endif // ANIMATEDOBJECT_H_
