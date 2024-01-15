
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"
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

unsigned int texture1old;

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

  engine.getWindow().setMouseCursorGrabbed(true);
  engine.getWindow().setMouseCursorVisible(false);

  lastMousePos = sf::Mouse::getPosition(engine.getWindow());

  engine.setLoopFunction(loopFun);

  engine.loop();

  engine.getWindow().setMouseCursorGrabbed(false);
}

/**
 *@brief
 *
 *This class assumes texture unit 0 is used for diffuse texture and texture unit
 *1 is used for specular map.
 **/
class Texture {

public:
  enum class TextureType { diffuse, specular };

  /**
   *@brief Retuns corespnding texture unit for the type.
   **/
  static GLenum getTextureTypeUnit(const TextureType type) {
    switch (type) {
    case TextureType::diffuse:
      return GL_TEXTURE0;
      break;
    case TextureType::specular:
      return GL_TEXTURE1;
      break;
    default:
      LOGERROR << "TextureType not handled\n";
      std::abort();
    }
  };

  void bind() {
    glActiveTexture(getTextureTypeUnit(m_type));
    glBindTexture(GL_TEXTURE_2D, m_id);
  }

  TextureType m_type;

  GLuint m_id;

  // Only PNG / jpeg
  Texture(const std::string path, TextureType type) : m_type(type) {
    bind();

    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps

    int width, height, nrChannels;
    unsigned char *data =
        stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

    LOGINFO << path << " has " << nrChannels << " chanels\n";

    if (data) {

      GLenum format;
      switch (nrChannels) {
      case 3:
        format = GL_RGB;
        break;
      case 4:
        format = GL_RGBA;
        break;
      default:
        LOGERROR << "Chanel count " << nrChannels << "is not handled ";
        std::abort();
        break;
      }

      // note that the awesomeface.png has transparency and thus an alpha
      // channel, so make sure to tell OpenGL the data type is  ? of GL_RGBA?
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format,
                   GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
    } else {
      std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
  }
};

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

  engine.getCamera().setSpeed(2);
  // engine.getWindow().setMouseCursorGrabbed(true);
  // engine.getWindow().setMouseCursorVisible(false);

  engine.setMaxFps(5);

  engine.setProjectionType(Engine::ProjectionType::perspective);
}
Texture texture1{"../engine/resources/textures/container.jpg",
                 Texture::TextureType::diffuse};
Texture texture2{"../engine/resources/textures/awesomeface.png",
                 Texture::TextureType::specular};

void loopFun() {

  // bind textures on corresponding texture units
  // glActiveTexture(GL_TEXTURE0);
  // glBindTexture(GL_TEXTURE_2D, texture1.m_id);
  // glActiveTexture(GL_TEXTURE1);
  // glBindTexture(GL_TEXTURE_2D, texture2.m_id);

  texture1.bind();
  texture2.bind();

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
