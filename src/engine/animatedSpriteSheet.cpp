#include "animatedSpriteSheet.hpp"
#include "log.hpp"
#include <fstream>
#include <functional>
#include <string>

std::istream &operator>>(std::istream &is,
                         AnimatedSpriteSheet::AnimationFrameData &afd) {

  return is;
}

AnimatedSpriteSheet::AnimatedSpriteSheet(std::string_view path) {
  std::string configFilePath{static_cast<std::string>(path) + "/config.txt"};

  std::fstream configFile{configFilePath};

  if (!configFile.is_open()) {
    LOGERROR << "opening config file failed it should be at " << configFilePath
             << "\n";
    return;
  }

  int currentAnimationBeingLoaded{-1};
  animationData_t animationDataBeingLoaded{};

  while (!configFile.eof()) {
    std::string line{};

    // load line, gnore lines that are commnets
    do {
      std::getline(configFile, line);
    } while (line.starts_with("#"));

    // load animation
    if (line.starts_with("ANIMATION")) {
      LOGINFO << "loading animation data\n";
      ++currentAnimationBeingLoaded;
      if (currentAnimationBeingLoaded >= 0) {
        // push the animation data and reset buffer for next animation.
        m_animationsData.push_back(animationDataBeingLoaded);
        animationDataBeingLoaded = {};
      }
    }

    // load frame
    if (line.starts_with("FRAME")) {
      LOGINFO << "loading frame data\n";
      // if frame is loaded but no animation is being loaded
      if (currentAnimationBeingLoaded == -1) {
        LOGERROR << "corrupted config file FRAME before ANIMATION\n";
        return;
      }
    }
  };

  configFile.close();
};
