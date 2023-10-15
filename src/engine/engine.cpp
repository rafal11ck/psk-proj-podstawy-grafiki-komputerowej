#include "engine.hpp"
#include "point2d.hpp"
#include "primitiveRenderer.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <string_view>

Engine Engine::s_singletonInstance{Engine()};

Engine &Engine::getEngine() { return s_singletonInstance; }

std::ostream &Engine::getOutStream() { return m_outStream; };

Point2d Engine::getWindowDimensions() const {
  return {m_mainWindow.getSize().x, m_mainWindow.getSize().y};
}

void Engine::setMaxFrameRate(int fps) { m_mainWindow.setFramerateLimit(fps); }

void handleEvents(sf::RenderWindow &window) {
  for (auto event = sf::Event{}; window.pollEvent(event);) {
    if (event.type == sf::Event::Closed) {
      window.close();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
      window.close();
  }
}

/**
 * @brief Render stuff
 */
void render(sf::RenderWindow &window) {
  window.clear();

  for (int i{}; i < 500; ++i) {
    PrimitiveRenderer::drawPoint({100 + i, 100});
  }

  Point2d origin{Engine::getEngine().getWindowDimensions().getX() / 2,
                 Engine::getEngine().getWindowDimensions().getY() / 2};

  for (auto offset : std::vector<Point2d>{
           {15, -55},  {35, -55},  {55, -55},  {55, -35},  {55, -15},
           {55, 15},   {55, 35},   {55, 55},   {35, 55},   {15, 55},
           {-15, -55}, {-35, -55}, {-55, -55}, {-55, -35}, {-55, -15},
           {-55, 15},  {-55, 35},  {-55, 55},  {-35, 55},  {-15, 55},
       }) {
    PrimitiveRenderer::drawLineIterative(origin, origin + offset);
  }

  window.display();
}

void Engine::loop() {
  m_outStream << "Engine loop\n";
  auto &window = m_mainWindow;

  // Clock for ticks.
  sf::Clock clock{};
  // Difference in time accumulator.
  sf::Time dTime{};

  while (window.isOpen()) {
    // handleEvents
    handleEvents(window);

    dTime += clock.restart();
    while (dTime >= m_tickTimeStep) {
      dTime -= m_tickTimeStep;

      // doLogic();
    }

    // render
    render(window);
  }

  m_outStream << "Engine loop done\n";
}

Engine::Engine(sf::VideoMode mode, std::string title) { init(mode, title); };

void Engine::init(sf::VideoMode mode, std::string title) {
  m_outStream << "Engine init\n";
  m_mainWindow.create(mode, title);
}
