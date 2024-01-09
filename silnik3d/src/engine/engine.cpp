#include "engine.hpp"
#include "shader.hpp"
#include <GL/glew.h>
#include <iostream>
#include <string>
#define TRACE
#include "resources.hpp"
#include "transformable.hpp"
#include <log.hpp>

Engine *Engine::s_instance{nullptr};

Engine &Engine::getInstance() {

  if (s_instance == nullptr) {
    s_instance = new Engine;
  }
  return *s_instance;
};

sf::Time Engine::getLastFrameDuration() const {
  return m_clockFrame.getElapsedTime();
}

Engine &Engine::buildWindow(sf::ContextSettings settings) {
  LOGTRACEN;
  // create the window
  m_window.create(sf::VideoMode(800, 600), "dev", sf::Style::Default, settings);

  m_window.setVerticalSyncEnabled(true);

  // activate the window
  m_window.setActive(true);

  // Opengl extension load
  glewInit();

  // Enable Z buffer
  glEnable(GL_DEPTH_TEST);

  return *this;
}

void Engine::loop() {
  LOGINFO << "Main loop is now running\n";
  // run the main loop
  isLoopRunning = true;

  const std::string basicShaderPath{std::string(getResourcesPath()) +
                                    "/shaders/basic/"};
  Shader basicShader{
      std::string(basicShaderPath + "basic_vertex.glsl").c_str(),
      std::string(basicShaderPath + "basic_fragment.glsl").c_str()};

  const std::string lightShaderPath{std::string(getResourcesPath()) +
                                    "shaders/light/"};

  Shader lighthader{
      std::string(basicShaderPath + "light_vertex.glsl").c_str(),
      std::string(basicShaderPath + "light_fragment.glsl").c_str()};

  while (isLoopRunning) {
    m_lastFrameDuration = m_clockFrame.restart();
    // handle events
    handleEvents();

    m_loopFunction();

    render(basicShader, lighthader);

    //  end the current frame (internally swaps the front and back buffers)
    m_window.display();
  }
}

const sf::Window &Engine::getWindow() const { return m_window; };
sf::Window &Engine::getWindow() { return m_window; };

Engine &Engine::setEventHandler(sf::Event::EventType eventType,
                                eventHandler_t handler) {
  m_eventHandlers[eventType] = handler;
  return *this;
}

Engine &Engine::setMaxFps(int fps) {
  m_window.setFramerateLimit(fps);
  return *this;
}

void Engine::addShape(Shape *shape) { m_shapes.push_back(shape); };

Engine::Engine() {
  LOGTRACEN;
  m_eventHandlers.fill([](const sf::Event &event) {});
  buildWindow();
}

void Engine::handleEvents() {
  sf::Event event;
  while (m_window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      // end the program
      isLoopRunning = false;
    } else if (event.type == sf::Event::Resized) {
      // adjust the viewport when the window is resized
      glViewport(0, 0, event.size.width, event.size.height);
    }

    m_eventHandlers[event.type](event);
  }
}

void Engine::render(Shader &shader, Shader lightShader) {

  for (const auto &shape : m_shapes) {
    shape->draw(shader);
  }
}
