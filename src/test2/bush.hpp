#ifndef BUSH_HPP_
#define BUSH_HPP_

#include "SFML/Graphics/Rect.hpp"
#include "animatedObject.hpp"
#include <string_view>

class Bush : public AnimatedObject {
  static constexpr std::string_view s_spriteSheetPath{"resource/bush/bush.png"};
  int m_aninmationFrameIndicator{};
  float m_animationFrameDuration{1};
  float m_animationTimer{};

public:
  Bush();
  ~Bush();

  virtual void animate();

private:
  void nextSprite();
  sf::IntRect getCurrentSpriteRectangle(int frameNumber);
};

#endif // BUSH_HPP_
