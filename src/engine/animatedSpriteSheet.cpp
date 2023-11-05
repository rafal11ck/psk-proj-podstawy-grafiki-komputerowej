#include "animatedSpriteSheet.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "log.hpp"
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <string>
#include <string_view>

std::istream &operator>>(std::istream &is,
                         AnimatedSpriteSheet::AnimationFrameData &afd) {
  is >> afd.m_position;
  is >> afd.m_size;
  is >> afd.m_duration;
  return is;
}

AnimatedSpriteSheet::AnimatedSpriteSheet(std::string_view path) {
  loadFromConfigFile(path);
};

void AnimatedSpriteSheet::loadFrame(std::istream &stream,
                                    animationData_t &animationData) {
  LOGINFO << "loading frame data\n";
  // load Frame data
  AnimationFrameData fdat{};
  stream >> fdat;
  // LOGINFO << fdat.m_position << " " << fdat.m_size << " " <<
  // fdat.m_duration
  //         << '\n';

  // add frame data to animation
  animationData.push_back(fdat);
  stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
};

void AnimatedSpriteSheet::loadSpritesheet(
    std::istream &stream, std::string_view configFileDirectoryPath) {
  LOGINFO << "loading spritesheet data\n";
  std::string spriteSheetRelPath{};
  stream >> spriteSheetRelPath;
  spriteSheetRelPath =
      std::string(configFileDirectoryPath) + "/" + spriteSheetRelPath;

  loadFromFile(spriteSheetRelPath);

  stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void AnimatedSpriteSheet::loadFromConfigFile(std::string_view pathToDir) {
  std::string configFilePath{static_cast<std::string>(pathToDir) +
                             "/config.txt"};
  // open file
  std::fstream configFile{configFilePath};
  if (!configFile.is_open()) {
    LOGERROR << "opening config file failed it should be at " << configFilePath
             << "\n";
    return;
  }

  animationData_t *animationDataBeingLoaded{NULL};
  std::string line{};

  while (!configFile.eof()) {
    line = "";
    // load line, ignore lines that are commnets
    do {
      std::getline(configFile, line);
    } while (line.starts_with("#"));

    // load spritesheet
    if (line.starts_with("SPRITESHEET")) {
      loadSpritesheet(configFile, pathToDir);
    } else if (line.starts_with("ANIMATION")) {
      // Add new animation and change pointer
      LOGINFO << "loading animation data\n";
      m_animationsData.push_back({});
      animationDataBeingLoaded = {&m_animationsData.back()};
      configFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    // load frame
    else if (line.starts_with("FRAME")) {
      if (animationDataBeingLoaded == NULL)
        LOGERROR << "config file is corrupted, FRAME before ANIMATION?";
      loadFrame(configFile, *animationDataBeingLoaded);
    }
    // not known
    else {
      // empty line ignore
      if (line == "") {
        continue;
      }
      // invalid line
      LOGWARN << "not recegnized config option: " << line
              << " in file: " << configFilePath << '\n';
    }
  }
  // close file
  configFile.close();
}
