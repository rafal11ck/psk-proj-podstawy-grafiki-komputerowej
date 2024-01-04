#include "SFML/System/Clock.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "engine.hpp"

#define TRACE
#include "log.hpp"

#include "shader.hpp"
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <camera.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>

#include <iostream>
#include <stb/stb_image.h>

Engine &engine{Engine::getInstance()};

Camera camera{{-0.0f, 0.f, -4.f}};
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

sf::Vector2i lastMousePos{};

// cube vertices
float vertices[] = {
    -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.5f,  -0.5f, -0.5f,
    0.0f,  0.0f,  -1.0f, 0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f,
    0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, -0.5f, 0.5f,  -0.5f,
    0.0f,  0.0f,  -1.0f, -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f,

    -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.5f,  -0.5f, 0.5f,
    0.0f,  0.0f,  1.0f,  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  -0.5f, 0.5f,  0.5f,
    0.0f,  0.0f,  1.0f,  -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,

    -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  -0.5f, 0.5f,  -0.5f,
    -1.0f, 0.0f,  0.0f,  -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  -0.5f, -0.5f, 0.5f,
    -1.0f, 0.0f,  0.0f,  -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,

    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.5f,  0.5f,  -0.5f,
    1.0f,  0.0f,  0.0f,  0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,
    0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.5f,  -0.5f, 0.5f,
    1.0f,  0.0f,  0.0f,  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.5f,  -0.5f, -0.5f,
    0.0f,  -1.0f, 0.0f,  0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,
    0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  -0.5f, -0.5f, 0.5f,
    0.0f,  -1.0f, 0.0f,  -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,

    -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.5f,  0.5f,  -0.5f,
    0.0f,  1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  -0.5f, 0.5f,  0.5f,
    0.0f,  1.0f,  0.0f,  -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f};

unsigned int VBO, cubeVAO;
unsigned int lightCubeVAO;

void init();
void loopFun();
void cameraMouseHandle(const sf::Event ev);

Shader lightingShader("vertexLighting.glsl", "fragmentLighting.glsl");
Shader lightSourceShader("vertexLightSource.glsl", "fragmentLightSource.glsl");

int main() {

  LOGTRACEN;

  init();
  std::cout << "Init done\n";

  engine.setLoopFunction(loopFun);
  engine.loop();
  glDeleteVertexArrays(1, &cubeVAO);
  glDeleteVertexArrays(1, &lightCubeVAO);
  glDeleteBuffers(1, &VBO);
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
  // first, configure the cube's VAO (and VBO)
  glGenVertexArrays(1, &cubeVAO);
  glGenBuffers(1, &VBO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindVertexArray(cubeVAO);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  // normal attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));

  glEnableVertexAttribArray(1);

  // second, configure the light's VAO (VBO stays the same; the vertices are the
  // same for the light object which is also a 3D cube)
  glGenVertexArrays(1, &lightCubeVAO);
  glBindVertexArray(lightCubeVAO);

  // we only need to bind to the VBO (to link it with glVertexAttribPointer), no
  // need to fill it; the VBO's data already contains all we need (it's already
  // bound, but we do it again for educational purposes)
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  camera.m_movementSpeed = 250;

  lastMousePos = sf::Mouse::getPosition(engine.getWindow());

  engine.getWindow().setMouseCursorGrabbed(true);
  engine.getWindow().setMouseCursorVisible(false);

  engine.setEventHandler(sf::Event::EventType::MouseMoved, cameraMouseHandle);
  engine.setMaxFps(75);
}

void loopFun() {

  handleCamera();

  glClearColor(0.0, 0.2f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // be sure to activate shader when setting uniforms/drawing objects
  lightingShader.use();
  lightingShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
  lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
  lightingShader.setVec3("lightPos", lightPos);
  lightingShader.setVec3("viewPos", camera.m_position);

  const sf::Vector2u screenSize = engine.getWindow().getSize();

  // view/projection transformations
  glm::mat4 projection = glm::perspective(glm::radians(camera.m_zoom),
                                          static_cast<float>(screenSize.x) /
                                              static_cast<float>(screenSize.y),
                                          0.1f, 100.0f);
  glm::mat4 view = camera.getViewMatrix();
  lightingShader.setMat4("projection", projection);
  lightingShader.setMat4("view", view);

  // world transformation
  glm::mat4 model = glm::mat4(1.0f);
  lightingShader.setMat4("model", model);

  // render the cube
  glBindVertexArray(cubeVAO);
  glDrawArrays(GL_TRIANGLES, 0, 36);

  // also draw the lamp object
  lightSourceShader.use();
  lightSourceShader.setMat4("projection", projection);
  lightSourceShader.setMat4("view", view);
  model = glm::mat4(1.0f);
  model = glm::translate(model, lightPos);
  model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
  lightSourceShader.setMat4("model", model);

  glBindVertexArray(lightCubeVAO);
  glDrawArrays(GL_TRIANGLES, 0, 36);
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
