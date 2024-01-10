
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "engine.hpp"
#include <glm/ext/matrix_clip_space.hpp>

#define TRACE
#include "log.hpp"

#include "model.hpp"
#include "shader.hpp"
#include <camera.hpp>
#include <glm/glm.hpp>

#include <assimp/Importer.hpp>

#include <resources.hpp>

Engine &engine{Engine::getInstance()};

Camera camera{{0.f, 0.f, 30.f}};

Shader ourShader("vertex.glsl", "fragment.glsl");

Model ourModel(std::string(getResourcesPath()) +
               "/objects/backpack/backpack.obj");

sf::Vector2i lastMousePos{};

void init();
void loopFun();
void cameraMouseHandle(const sf::Event ev);

int main() {
  LOGTRACEN;

  init();
  std::cout << "Init done\n";

  engine.setLoopFunction(loopFun);
  engine.loop();
}

// Move camera around
void handleCamera() {
  // Only accept one diretion movement on axis
  auto handle{[](sf::Keyboard::Key key1, sf::Keyboard::Key key2,
                 Camera::Camera_Movement dir1, Camera::Camera_Movement dir2) {
    if (sf::Keyboard::isKeyPressed(key1) ^ sf::Keyboard::isKeyPressed(key2)) {
      if (sf::Keyboard::isKeyPressed(key1)) {
        camera.processKeyboard(dir1, engine.getLastFrameDuration().asSeconds());
      } else if (sf::Keyboard::isKeyPressed(key2)) {
        camera.processKeyboard(dir2, engine.getLastFrameDuration().asSeconds());
      }
    }
  }};

  handle(sf::Keyboard::Key::W, sf::Keyboard::Key::S,
         Camera::Camera_Movement::FORWARD, Camera::Camera_Movement::BACKWARD);

  handle(sf::Keyboard::Key::A, sf::Keyboard::Key::D,
         Camera::Camera_Movement::LEFT, Camera::Camera_Movement::RIGHT);
}

void init() {

  LOGINFO << getResourcesPath() << '\n';

  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

  camera.m_movementSpeed = 250;

  engine.getWindow().setMouseCursorGrabbed(true);
  engine.getWindow().setMouseCursorVisible(false);

  lastMousePos = sf::Mouse::getPosition(engine.getWindow());

  engine.setEventHandler(sf::Event::EventType::MouseMoved, cameraMouseHandle);

  engine.setMaxFps(75);
}

void loopFun() {

  handleCamera();

  glClearColor(0.0, 0.2f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // pass projection matrix to shader (note that in this case it could change
  // every frame)
  glm::mat4 projection =
      glm::perspective(glm::radians(camera.m_zoom),
                       static_cast<float>(engine.getWindow().getSize().x) /
                           static_cast<float>(engine.getWindow().getSize().y),
                       0.1f, 100.0f);

  // camera/view transformation
  glm::mat4 view = camera.getViewMatrix();

  ourShader.setMat4("projection", view);
  ourShader.setMat4("view", view);

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(0.f, 0.f, -3.f));
  model = glm::scale(model, glm::vec3(1.f, 1.f, 1.f));
  ourShader.setMat4("model", model);

  ourModel.Draw(ourShader);
}

void cameraMouseHandle(const sf::Event ev) {

  static float yaw{};
  static float pitch{};

  float xOffset{static_cast<float>(ev.mouseMove.x) - lastMousePos.x};
  float yOffset{static_cast<float>(lastMousePos.y - ev.mouseMove.y)};

  sf::Vector2i middle{static_cast<int>(engine.getWindow().getSize().x * 0.5f),
                      static_cast<int>(engine.getWindow().getSize().y * 0.5f)};

  // sf::Mouse::setPosition(middle, engine.getWindow());

  lastMousePos = sf::Mouse::getPosition(engine.getWindow());

  camera.processMouseMovement(xOffset, yOffset);
}
