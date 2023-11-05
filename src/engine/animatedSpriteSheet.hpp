#ifndef ANIMATEDSPRITESHEET_H_
#define ANIMATEDSPRITESHEET_H_

#include "animatedObject.hpp"
#include <istream>
#include <string_view>
class AnimatedSpriteSheet : public AnimatedObject {

public:
  struct AnimationFrameData {
    //** Duration of frame */
    float m_duration;
    //** size of sprite  */
    Point2d m_size;
    //** position of sprite */
    Point2d m_position;

    friend std::istream &operator>>(std::istream &is, AnimationFrameData &afd);
  };

  using animationData_t = std::vector<AnimationFrameData>;

public:
  AnimatedSpriteSheet(std::string_view path);

private:
  /**
   *@brief Adds animation
   **/
  void addAnimation(animationData_t animationData);

  void nextFrame();

  /**
   * @brief load frame data from stream
   */
  void loadFrame(std::istream &stream, animationData_t &animationData);

  void loadSpritesheet(std::istream &stream,
                       std::string_view configFileDirectoryPath);

  void loadFromConfigFile(std::string_view pathToDir);

private:
  /**
   * Colecction of animations.
   * */
  std::vector<animationData_t> m_animationsData;

  /**
   * Indicates index of current animation in m_animationsData.
   * */
  int m_currentAnimationTypeIndex;

  int m_currentFrameId{};
  float m_currentAnimationFrameDuration{};
  float m_animationTimer{};
};

#endif // ANIMATEDSPRITESHEET_H_
