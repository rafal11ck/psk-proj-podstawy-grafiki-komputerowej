#ifndef ANIMATEDOBJECT_H_
#define ANIMATEDOBJECT_H_

#include "GameObject.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "point2d.hpp"
#include <vector>

class AnimatedObject : public GameObject,
                       public sf::Sprite,
                       public sf::Texture {

public:
  virtual ~AnimatedObject(){};

  virtual void animate();

  void setPosition(Point2d pos) override;

private:
};

#endif // ANIMATEDOBJECT_H_
