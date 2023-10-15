#include "engine.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <string_view>

Engine Engine::s_singletonInstance{Engine()};

Engine &Engine::getEngine() { return s_singletonInstance; }

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

void render(sf::RenderWindow &window) {
  window.clear();

  window.display();
}

void Engine::loop() {
  m_outStream << "Engine loop\n";
  auto &window = m_mainWindow;

  // Clock for ticks.
  sf::Clock clock;
  // Difference in time accumulator.
  sf::Time dTime;
  // Gaps in time between ticks.
  sf::Time tickTimeStep;

  while (window.isOpen()) {
    // handleEvents
    handleEvents(window);

    // render
    render(window);
  }
}

Engine::Engine(sf::VideoMode mode, std::string title) { init(mode, title); };

void Engine::init(sf::VideoMode mode, std::string title) {
  m_outStream << "Engine init\n";
  m_mainWindow.create(mode, title);
}
