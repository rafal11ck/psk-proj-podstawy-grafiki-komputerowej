#include "animatedSpriteSheet.hpp"
#include "log.hpp"
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <string>

std::istream &operator>>(std::istream &is,
                         AnimatedSpriteSheet::AnimationFrameData &afd) {
  is >> afd.m_position;
  is >> afd.m_size;
  is >> afd.m_duration;
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
  std::string line{};

  auto loadAnimation{[&]() {
    LOGINFO << "loading animation data\n";
    ++currentAnimationBeingLoaded;
    if (currentAnimationBeingLoaded >= 0) {
      // push the animation data and reset buffer for next animation.
      m_animationsData.push_back(animationDataBeingLoaded);
      animationDataBeingLoaded = {};
    }
    configFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }};

  while (!configFile.eof()) {
    line = "";
    // load line, ignore lines that are commnets
    do {
      std::getline(configFile, line);
    } while (line.starts_with("#"));

    if (line.starts_with("ANIMATION")) {
      // load animation
      loadAnimation();
    } else

      // load frame
      if (line.starts_with("FRAME")) {
        LOGINFO << "loading frame data\n";
        // if frame is loaded but no animation is being loaded
        if (currentAnimationBeingLoaded == -1) {
          LOGERROR << "corrupted config file FRAME before ANIMATION\n";
          return;
        }
        // load Frame data
        AnimationFrameData fdat{};
        configFile >> fdat;
        // LOGINFO << fdat.m_position << " " << fdat.m_size << " " <<
        // fdat.m_duration
        //         << '\n';

        // add frame data to animation
        animationDataBeingLoaded.push_back(fdat);
        configFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
    if (line.starts_with("SPRITESHEET")) {
      LOGINFO << "loading spritesheet data\n";
      std::string spriteSheetRelPath{};
      configFile >> spriteSheetRelPath;
      spriteSheetRelPath = std::string(path) + "/" + spriteSheetRelPath;
      int x{};
      configFile >> x;
      int y{};
      configFile >> y;
      LOGINFO << spriteSheetRelPath << " " << x << y << '\n';
      configFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else {
      if (line == "")
        continue;
      LOGWARN << "not recegnized config option: " << line
              << " in file: " << configFilePath << '\n';
    }
  };

  configFile.close();
};
