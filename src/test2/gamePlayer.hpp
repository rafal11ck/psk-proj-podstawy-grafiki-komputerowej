#ifndef GAMEPLAYER_H_
#define GAMEPLAYER_H_

#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Vector2.hpp"
#include "animatedObject.hpp"
#include "player.hpp"
#include "point2d.hpp"

class GamePlayer : public Player {
public:
  static constexpr std::string_view s_spriteSheetPath{
      "resource/player/spritesheet.png"};

  enum class AnimationType {
    standing,
    moveNorth,
    moveEast,
    moveSouth,
    moveWest,
    moveSpecial,
    count
  };

public:
  GamePlayer();

  virtual void animate() override;
  virtual void update() override;

private:
  int m_aninmationFrameIndicator{};
  float m_animationFrameDuration{.5};
  float m_animationTimer{};
  AnimationType m_animationType{AnimationType::standing};

  void nextAnimationFrame();
  void updateTextureRect();

  void setAnimationType(AnimationType type);

  AnimationType getAnimationTypeOf(MoveDirection moveDirection) const;
  int getFrameCountOfAnimation(AnimationType type) const;
  sf::IntRect getCurrentAnimationFrameSpriteRectangle() const;
  int getRowOfAnimation() const;
};
#endif // GAMEPLAYER_H_
