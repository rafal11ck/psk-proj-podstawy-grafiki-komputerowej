#include "animatedSpriteSheet.hpp"
#include "engine.hpp"
#include "log.hpp"
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <string>
#include <string_view>

std::istream &operator>>(std::istream &is,
                         AnimatedSpriteSheet::AnimationFrameData &afd) {
  LOGTRACEN;
  is >> afd.m_position;
  is >> afd.m_size;
  is >> afd.m_duration;
  return is;
}

sf::IntRect AnimatedSpriteSheet::AnimationFrameData::toIntRect() const {
  LOGTRACEN;
  return {static_cast<int>(m_position.getX()),
          static_cast<int>(m_position.getY()), static_cast<int>(m_size.getX()),
          static_cast<int>(m_size.getY())};
}

AnimatedSpriteSheet::AnimatedSpriteSheet(std::string_view path) {
  std::string pathh{std::string(path) + "/spritesheet.png"};
  LOGINFO << pathh << '\n';
  loadFromConfigFile(path);

  setTexture(*this);
  setFrame(getCurrentAnimationFrameData());
  // setFrame(getCurrentAnimationFrameData());
};

void AnimatedSpriteSheet::animate() {
  LOGTRACEN;
  m_animationTimer += Engine::getInstance().getLastFrameDuration().asSeconds();
  // if duration of frame not exhaused do nothing;
  if (m_animationTimer < getCurrentAnimationFrameDuration())
    return;
  nextFrame();
}

void AnimatedSpriteSheet::nextFrame() {
  LOGTRACEN;
  // change frame
  ++m_currentFrameId;
  m_currentFrameId %= getCurrentAnimationFrameCount();
  setFrame(getCurrentAnimationFrameData());
}

int AnimatedSpriteSheet::getCurrentAnimationFrameCount() const {
  LOGTRACEN;
  return m_animationsData[m_currentAnimationTypeIndex].size();
}

const AnimatedSpriteSheet::AnimationFrameData &
AnimatedSpriteSheet::getCurrentAnimationFrameData() const {
  LOGTRACEN;
  if (m_animationsData.size() == 0 ||
      m_animationsData.size() < m_currentAnimationTypeIndex) {
    LOGWARN << "No animation data\n";
  } else if (m_animationsData[m_currentAnimationTypeIndex].size() == 0 ||
             m_animationsData[m_currentAnimationTypeIndex].size() <
                 m_currentAnimationTypeIndex) {
    LOGWARN << "No frame data in animation " << m_currentAnimationTypeIndex
            << '\n';
  }
  return m_animationsData[m_currentAnimationTypeIndex][m_currentFrameId];
}

float AnimatedSpriteSheet::getCurrentAnimationFrameDuration() const {
  LOGTRACEN;
  return getCurrentAnimationFrameData().m_duration;
};

void AnimatedSpriteSheet::setFrame(const AnimationFrameData &frameData) {
  LOGTRACEN;
  setTextureRect(frameData.toIntRect());
  m_animationTimer = 0;
}

void AnimatedSpriteSheet::loadFrame(std::istream &stream,
                                    animationData_t &animationData) {
  LOGTRACEN;
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
      //     LOGINFO << "loading animation data\n";
      m_animationsData.push_back({});
      animationDataBeingLoaded = {&m_animationsData.back()};
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
