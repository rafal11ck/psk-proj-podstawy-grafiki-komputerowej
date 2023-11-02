#ifndef ANIMATEDOBJECT_H_
#define ANIMATEDOBJECT_H_

#include "GameObject.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

class AnimatedObject : public GameObject,
                       public sf::Sprite,
                       public sf::Texture {

public:
  virtual ~AnimatedObject(){};

  virtual void setPosition(Point2d pos);

  virtual void animate();
};

#endif // ANIMATEDOBJECT_H_
