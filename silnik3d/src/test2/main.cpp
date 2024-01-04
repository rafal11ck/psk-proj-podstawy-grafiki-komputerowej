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

Camera camera{{0.f, 0.f, 3.f}};

unsigned int texture1, texture2;

Shader ourShader{"vertex.glsl", "fragment.glsl"};

// cube vertices
float vertices[] = {
    -0.5f, -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, 0.5f,  0.5f,  -0.5f,
    0.5f,  0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, -0.5f, -0.5f,

    -0.5f, -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f, -0.5f, 0.5f,

    -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  -0.5f, -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f,  0.5f,

    0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  -0.5f, 0.5f,  -0.5f, -0.5f,
    0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f,  0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f,
    0.5f,  -0.5f, 0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, -0.5f,

    -0.5f, 0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  -0.5f};

// world space positions of our cubes
glm::vec3 cubePositions[] = {
    glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
    glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};
unsigned int VBO, VAO;

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
  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  camera.m_movementSpeed = 250;

  engine.getWindow().setMouseCursorGrabbed(true);
  engine.getWindow().setMouseCursorVisible(false);

  lastMousePos = sf::Mouse::getPosition(engine.getWindow());

  engine.setEventHandler(sf::Event::EventType::MouseMoved, cameraMouseHandle);

  engine.setMaxFps(75);
}

void loopFun() {

  handleCamera();

  // bind textures on corresponding texture units
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture1);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, texture2);

  glClearColor(0.0, 0.2f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  ourShader.use();

  // pass projection matrix to shader (note that in this case it could change
  // every frame)
  glm::mat4 projection =
      glm::perspective(glm::radians(camera.m_zoom),
                       static_cast<float>(engine.getWindow().getSize().x) /
                           static_cast<float>(engine.getWindow().getSize().y),
                       0.1f, 100.0f);

  ourShader.setMat4("projection", projection);

  // camera/view transformation
  glm::mat4 view = camera.getViewMatrix();
  ourShader.setMat4("view", view);

  // render boxes
  glBindVertexArray(VAO);
  for (unsigned int i = 0; i < 10; i++) {
    // calculate the model matrix for each object and pass it to shader before
    // drawing
    glm::mat4 model = glm::mat4(
        1.0f); // make sure to initialize matrix to identity matrix first
    model = glm::translate(model, cubePositions[i]);
    float angle = 20.0f * i;
    model =
        glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
    ourShader.setMat4("model", model);

    glDrawArrays(GL_TRIANGLES, 0, 36);
  }
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

  static constexpr float sensitivity = 0.3f;
  xOffset *= sensitivity;
  yOffset *= -sensitivity;

  camera.m_yaw += xOffset;
  camera.m_pitch += yOffset;

  if (pitch > 89.0f) {
    pitch = 89.0f;
  }

  if (pitch < -89.0f) {
    pitch = 89.0f;
  }

  camera.updateCameraVectors();
}
