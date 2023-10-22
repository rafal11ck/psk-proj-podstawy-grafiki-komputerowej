
#include "engine.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/VideoMode.hpp"
#include <iostream>

#define LOGTRACE                                                               \
  Engine::s_logStream << __FILE_NAME__ << " " << __PRETTY_FUNCTION__ << '\n';

#define LOGINFO                                                                \
  Engine::s_logStream << "\033[35m" << __FILE_NAME__ << " "                    \
                      << __PRETTY_FUNCTION__ << "\033[0m\n";

std::ostream &Engine::s_logStream{std::cerr};

Engine *Engine::s_instancePtr{nullptr};

Engine::Engine() {}
Engine::~Engine() {}

Engine &Engine::getInstance() {
  if (s_instancePtr == nullptr)
    s_instancePtr = new Engine;
  return *s_instancePtr;
}

Engine &Engine::setMaxFps(int fps) {
  LOGINFO
  m_maxFPS = fps;
  m_window.setFramerateLimit(fps);
  return getInstance();
}

Engine &Engine::setWindowTitle(std::string_view title) {
  LOGINFO
  m_windowTitle = title;
  return getInstance();
}

Engine &Engine::setResolution(Point2d resolution) {
  LOGINFO
  m_resoltuon = resolution;
  return getInstance();
}

Engine &Engine::buildWindow() {
  LOGINFO
  m_window.create({static_cast<unsigned int>(m_resoltuon.getX()),
                   static_cast<unsigned int>(m_resoltuon.getY())},
                  m_windowTitle);
  m_window.setFramerateLimit(m_maxFPS);
  return getInstance();
}

Point2d Engine::getResolution() const {
  LOGINFO
  return m_resoltuon;
}

void Engine::handleEvents() {
  LOGTRACE
  sf::Event event;
  while (m_window.pollEvent(event)) {
    if (event.type == sf::Event::Closed)
      m_window.close();
  }
}

void Engine::clear() { m_window.clear(); }

void Engine::render() {
  LOGTRACE

  m_window.display();
}

void Engine::loop() {
  LOGINFO
  while (m_window.isOpen()) {
    handleEvents();
    clear();
    render();
  }
}
