#define TRACE
#include <log.hpp>

#include <GL/glew.h>

#include "engine.hpp"
#include "resources.hpp"
#include "shader.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <ostream>

Engine *Engine::s_instance{nullptr};

const std::string Engine::defaultShaderDir{getResourcesPath() + "/shaders/"};

const std::string Engine::defaultShaderPathVertex{defaultShaderDir +
                                                  "vertex.glsl"};

const std::string Engine::defaultShaderPathFragment{defaultShaderDir +
                                                    "/fragment.glsl"};

Engine &Engine::getInstance() {

  if (s_instance == nullptr) {
    s_instance = new Engine;
  }
  return *s_instance;
};

sf::Time Engine::getLastFrameDuration() const { return m_lastFrameDuration; }

Engine &Engine::buildWindow(sf::ContextSettings settings) {
  LOGTRACEN;
  LOGINFO << "Building window.\n";
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

  // run the main loop
  isLoopRunning = true;
  while (isLoopRunning) {
    m_lastFrameDuration = m_clockFrame.restart();
    // handle events
    handleEvents();

    glClearColor(0.0, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_loopFunction();

    render();

    // end the current frame (internally swaps the front and back buffers)
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

void Engine::addDrawable(Drawable *drawable) {
  LOGINFO << "Adding drawable " << drawable << "\n";
  const bool didInsert = m_drawables.insert(drawable).second;
  if (!didInsert) {
    LOGWARN << "Attempted to add already existing drawable " << drawable
            << " !\n";
  }
};

void Engine::removeDrawable(Drawable *const drawable) {
  LOGINFO << "Removing drawable " << drawable << "\n";
  m_drawables.erase(drawable);
};

Camera &Engine::getCamera() { return m_camera; };

float Engine::getAspectRatio() const {
  return static_cast<float>(getWindow().getSize().x) / getWindow().getSize().y;
}

glm::mat4 Engine::computeProjectionMatrix() const {
  glm::mat4 projection =
      glm::perspective(glm::radians(m_camera.getZoom()), getAspectRatio(),
                       clippingPlaneNear, clippingPlaneFar);
  return projection;
}

Engine::Engine() {
  LOGINFO << "Initializing Engine\n";
  m_eventHandlers.fill([](const sf::Event &event) {});
  buildWindow();

  LOGINFO << "Compiling default shader.\n";
  std::string shaderDir{getResourcesPath() + "/shaders/"};

  m_defaultShader =
      new Shader(defaultShaderPathVertex, defaultShaderPathFragment);

  m_defaultShader->use();

  LOGINFO << "Main loop is now running\n";
}

Engine::~Engine() {
  LOGTRACEN;

  /// Only deletes data pointed to by m_drawables. As keys from set will be
  /// remeved by it's own destructor.
  for (auto drawable : m_drawables) {
    LOGINFO << "Deleting drawable" << drawable << "\n";
    delete (drawable);
  }

  /// Deletes defaultshader it it's not nullptr.
  if (m_defaultShader != nullptr) {
    delete m_defaultShader;
  }
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

void Engine::render() {
  // LOGTRACEN;

  if (m_defaultShader == nullptr) {
    LOGERROR << "default shader does not exist\n";
    std::abort();
  }

  m_defaultShader->use();
  m_defaultShader->setMat4("projection", computeProjectionMatrix());

  for (auto drawable : m_drawables) {
    drawable->draw(*m_defaultShader);
  }
}
