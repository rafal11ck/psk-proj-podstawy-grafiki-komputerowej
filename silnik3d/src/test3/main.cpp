
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"
#include "texture.hpp"
#include <cstdlib>
#include <glm/geometric.hpp>

#define TRACE
#include "log.hpp"

#include "engine.hpp"
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

Camera &camera{engine.getCamera()};

Shader ourShader{"vertex.glsl", "fragment.glsl"};

float lastX{};
float lastY{};

// cube vertices
float vertices[] = {
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 0.0f,
    0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,

    -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,

    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
    0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 1.0f,
    0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

    -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f};

// world space positions of our cubes
glm::vec3 cubePositions[] = {
    glm::vec3(0.0f, 1.0f, -5.0f),   glm::vec3(2.0f, 5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
    glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};
unsigned int VBO, VAO;

sf::Vector2i lastMousePos{};

void init();
void loopFun();

int main() {

  LOGTRACEN;

  init();
  std::cout << "Init done\n";

  lastMousePos = sf::Mouse::getPosition(engine.getWindow());

  engine.setLoopFunction(loopFun);

  engine.loop();
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
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  // texture coord attribute
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // -------------------------------------------------------------------------------------------
  ourShader.use();
  ourShader.setInt("textureDiffuse", 0);
  ourShader.setInt("textureSpecular", 1);

  engine.setMaxFps(5);

  engine.setProjectionType(Engine::ProjectionType::perspective);
}
Texture texture1{
    Texture::TextureType::diffuse,
    "../engine/resources/textures/container.jpg",
};
Texture texture2{
    Texture::TextureType::specular,
    "../engine/resources/textures/awesomeface.png",
};

void loopFun() {

  glClearColor(0.0, 0.2f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  ourShader.use();

  // pass projection matrix to shader (note that in this case it could change
  // every frame)
  glm::mat4 projection = engine.computeProjectionMatrix();

  ourShader.setMat4("projection", projection);

  // camera/view transformation
  glm::mat4 view = camera.getViewMatrix();
  ourShader.setMat4("view", view);

  // render boxes
  glBindVertexArray(VAO);
  for (unsigned int i = 0; i < 10; i++) {

    texture1.bind();
    texture2.bind();

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

    texture1.unBind();
    texture2.unBind();
  }
}
