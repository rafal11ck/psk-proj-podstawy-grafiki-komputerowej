#include "engine.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/View.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/VideoMode.hpp"
#include "primitiveRenderer.hpp"
#include <iostream>

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
  m_windowTitle = title;
  return getInstance();
}

Engine &Engine::setResolution(Point2d resolution) {
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

Point2d Engine::getResolution() const { return m_resoltuon; }

void Engine::handleEvents() {
  sf::Event event;
  while (m_window.pollEvent(event)) {
    if (event.type == sf::Event::Closed)
      m_window.close();
    if (event.type == sf::Event::Resized) {

      // Update engine info
      m_resoltuon.setX(event.size.width);
      m_resoltuon.setY(event.size.height);
      // make new view
      sf::FloatRect view{0, 0, static_cast<float>(m_resoltuon.getX()),
                         static_cast<float>(m_resoltuon.getY())};
      m_window.setView(sf::View{view});

      s_logStream << "Resized\t" << event.size.width << '\t'
                  << event.size.height << '\n';
    }
  }
}

void Engine::clear() { m_window.clear(); }

void Engine::render() {
  PrimitiveRenderer::drawLine({{20, 20}, {220, 20}, {150, 150}},
                              PrimitiveRenderer::s_defaultColor, true);
}

void Engine::display() { m_window.display(); }

void Engine::loop() {
  LOGINFO
  while (m_window.isOpen()) {
    clear();
    handleEvents();
    m_loopFunction();
    render();
    display();
  }
}
