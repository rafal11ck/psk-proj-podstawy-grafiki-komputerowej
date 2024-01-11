#include "engine.hpp"
#include "log.hpp"
#include "shader.hpp"
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <cstddef>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

Engine &engine{Engine::getInstance()};

struct Vertex {
  glm::vec3 m_position{0.f};
};

namespace meshHelper {
class VertexArray {
  /// @brief Vertex array id;
  GLuint m_VAOid{};

public:
  VertexArray() { glGenVertexArrays(1, &m_VAOid); }

  void bind() { glBindVertexArray(m_VAOid); };

  static void unBind() { glBindVertexArray(0); };

  void setAttribPointer(GLuint layout, GLuint numOfValues, GLuint pointerVal) {
    bind();
    glVertexAttribPointer(layout, numOfValues, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex), reinterpret_cast<void *>(pointerVal));
    glEnableVertexAttribArray(layout);
  }
};

class VertexBuffer {
  /// @brief Vertex buffer object id
  GLuint m_VBO;

public:
  VertexBuffer() { glGenBuffers(1, &m_VBO); };

  void setData(std::vector<Vertex> verticies) {
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(Vertex),
                 verticies.data(), GL_STATIC_DRAW);
  }
};

class ElementBuffer {
  /// @brief Element buffer object id
  GLuint m_EBO;

public:
  ElementBuffer() { glGenBuffers(1, &m_EBO); };

  void setData(std::vector<GLuint> inicies) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, inicies.size() * sizeof(GLint),
                 inicies.data(), GL_STATIC_DRAW);
  }
};
}; // namespace meshHelper

class BasicMesh {
public:
  using verticies_t = std::vector<Vertex>;
  using indicies_t = std::vector<GLuint>;

private:
  /// @brief Vertex array object.
  meshHelper::VertexArray *m_VAO{nullptr};
  /// @biref Vericies collection.
  verticies_t m_verticies;
  /// @brief Elements collection.
  indicies_t m_elements;

protected:
  void initialize(verticies_t veritices, indicies_t indicies) {
    if (veritices.empty()) {
      LOGWARN << "Empty verticies";
    }
    if (indicies.empty()) {
      LOGWARN << "Empty indicies";
    }
  }

public:
  BasicMesh(){};
};

std::vector<Vertex> verticies{
    {glm::vec3{0.5f, 0.5f, 0.0f}},   // top right
    {glm::vec3{0.5f, -0.5f, 0.0f}},  // bottom right
    {glm::vec3{-0.5f, -0.5f, 0.0f}}, // bottom left
    {glm::vec3{-0.5f, 0.5f, 0.0f}}   // top left
};

std::vector<GLuint> indicies{0, 1, 3, 1, 2, 3};

Shader shader("vertex.glsl", "fragment.glsl");

int main() {

  meshHelper::VertexArray VAO{};
  VAO.bind();

  meshHelper::VertexBuffer VBO{};
  VBO.setData(verticies);

  meshHelper::ElementBuffer EBO{};
  EBO.setData(indicies);

  VAO.setAttribPointer(0, 3, offsetof(Vertex, m_position));

  VAO.unBind();

  engine.setLoopFunction([&]() {
    glClearColor(0.0, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();
    VAO.bind();
    glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_INT, 0);
  });

  engine.loop();
}
