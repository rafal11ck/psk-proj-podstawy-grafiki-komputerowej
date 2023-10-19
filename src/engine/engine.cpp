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

void Engine::render() {
  auto &window = m_mainWindow;
  window.clear();

  // test pixel draw
  for (int i{}; i < 200; ++i) {
    PrimitiveRenderer::drawPoint({100 + i, 100});
  }

  // test drawing lines
  Point2d origin{100 + 55, 200};

  for (auto offset : std::vector<Point2d>{
           {15, -55},  {35, -55},  {55, -55},  {55, -35},  {55, -15},
           {55, 15},   {55, 35},   {55, 55},   {35, 55},   {15, 55},
           {-15, -55}, {-35, -55}, {-55, -55}, {-55, -35}, {-55, -15},
           {-55, 15},  {-55, 35},  {-55, 55},  {-35, 55},  {-15, 55},
       }) {
    PrimitiveRenderer::drawLineIterative(origin, origin + offset);
    PrimitiveRenderer::drawLine(origin + 55 * 2, origin + 55 * 2 + offset);
    // triangle
    PrimitiveRenderer::drawTriangle({100, 260}, {250, 300}, {300, 400});
  }

  PrimitiveRenderer::drawLine({{100, 420}, {400, 450}, {300, 500}, {200, 410}});

  for (auto &drawAble : m_rendererDrawables) {
    drawAble->draw();
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
    render();
  }

  m_outStream << "Engine loop done\n";
}

Engine::Engine(sf::VideoMode mode, std::string title) { init(mode, title); };

void Engine::init(sf::VideoMode mode, std::string title) {
  m_outStream << "Engine init\n";
  m_mainWindow.create(mode, title);
}

Engine::~Engine() {
  for (auto it : m_rendererDrawables) {
    delete it;
  }
}
