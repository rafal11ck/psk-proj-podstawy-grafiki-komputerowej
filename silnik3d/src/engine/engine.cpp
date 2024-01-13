#include <cstdlib>
#define TRACE
#include <log.hpp>

#include <GL/glew.h>

#include "engine.hpp"
#include "resources.hpp"
#include "shader.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
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
    handleCameraKeyboard();

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

  glm::mat4 projection{};
  switch (m_projectionType) {
  case ProjectionType::perspective:
    projection =
        glm::perspective(glm::radians(m_camera.getZoom()), getAspectRatio(),
                         clippingPlaneNear, clippingPlaneFar);
    break;
  case ProjectionType::orthogonal:
    projection = glm::ortho(-getAspectRatio(), getAspectRatio(), -1.f, 1.f,
                            clippingPlaneNear, clippingPlaneFar);
    break;
  default:
    LOGERROR << "Projection type not handled (casted = "
             << static_cast<int>(m_projectionType) << ")\n";
    abort();
  }
  return projection;
}

void Engine::setCameraHandlingMouse(bool enbaled) {
  LOGINFO << "Setting engine camera rotation on mouse move to "
          << (enbaled ? "true" : "false") << "\n";
  m_engineHandleCameraOnMouseMove = enbaled;
}

void Engine::setCameraHandlingKeyboard(bool enbaled) {
  LOGINFO << "Setting engine camera move on keyboard to "
          << (enbaled ? "true" : "false") << "\n";
  m_cameraHandlingKeyboard = enbaled;
}

void Engine::setProjectionType(ProjectionType projectionType) {
  LOGINFO << "Setting projection type to (casted "
          << static_cast<int>(projectionType) << ")\n";
  m_projectionType = projectionType;
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
  m_defaultShader->setMat4("view", glm::mat4{1});

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

    switch (event.type) {
    case sf::Event::Closed:
      isLoopRunning = false;
      break;
    case sf::Event::Resized:
      // adjust the viewport when the window is resized
      glViewport(0, 0, event.size.width, event.size.height);
      break;
    case sf::Event::MouseMoved:
      handleCameraMouseMove(event);
      break;
    default:
      break;
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

  m_defaultShader->setMat4("view", getCamera().getViewMatrix());

  for (auto drawable : m_drawables) {
    drawable->draw(*m_defaultShader);
  }
}

void Engine::handleCameraMouseMove(const sf::Event ev) {
  if (!m_engineHandleCameraOnMouseMove) {
    return;
  }

  static sf::Vector2i lastMousePos{sf::Mouse::getPosition(getWindow())};

  float xOffset{static_cast<float>(ev.mouseMove.x) - lastMousePos.x};
  float yOffset{static_cast<float>(lastMousePos.y - ev.mouseMove.y)};

  sf::Vector2i middle{static_cast<int>(getWindow().getSize().x * 0.5f),
                      static_cast<int>(getWindow().getSize().y * 0.5f)};

  // sf::Mouse::setPosition(middle, engine.getWindow());

  lastMousePos = sf::Mouse::getPosition(getWindow());

  static constexpr float sensitivity = 0.3f;
  xOffset *= sensitivity;
  yOffset *= sensitivity;

  getCamera().processMouseMovement(xOffset, yOffset);
}

void Engine::handleCameraKeyboard() {
  if (!m_cameraHandlingKeyboard) {
    return;
  }

  // Only accept one diretion movement on axis
  auto handle{[&](sf::Keyboard::Key key1, sf::Keyboard::Key key2,
                  Camera::Camera_Movement dir1, Camera::Camera_Movement dir2) {
    if (sf::Keyboard::isKeyPressed(key1) ^ sf::Keyboard::isKeyPressed(key2)) {
      if (sf::Keyboard::isKeyPressed(key1)) {
        getCamera().processKeyboard(dir1, getLastFrameDuration().asSeconds());
      } else if (sf::Keyboard::isKeyPressed(key2)) {
        getCamera().processKeyboard(dir2, getLastFrameDuration().asSeconds());
      }
    }
  }};

  handle(sf::Keyboard::Key::W, sf::Keyboard::Key::S,
         Camera::Camera_Movement::FORWARD, Camera::Camera_Movement::BACKWARD);

  handle(sf::Keyboard::Key::A, sf::Keyboard::Key::D,
         Camera::Camera_Movement::LEFT, Camera::Camera_Movement::RIGHT);
};
