
#define TRACE
#include "log.hpp"

#include "engine.hpp"
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
  glm::vec3 m_normal{0.f};
  glm::vec3 m_texCord{0.f};
};

class VertexArray {
  /// @brief Vertex array id;
  GLuint m_VAOid{};

public:
  VertexArray() {

    LOGTRACEN;
    glGenVertexArrays(1, &m_VAOid);
  }

  void bind() { glBindVertexArray(m_VAOid); };

  static void unBind() { glBindVertexArray(0); };

  /**
   *
   *@param layout layout number that shader uses to access data.
   *@param size How many values are in one struct ex. (*3* floats).
   *@param offset offset in values count. (use offsetof())
   **/
  void setAttribPointer(GLuint layout, GLuint size, GLuint offset = 0) {
    bind();
    glVertexAttribPointer(layout, size, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<void *>(offset));
    glEnableVertexAttribArray(layout);
  }
};

class VertexBuffer {
  /// @brief Vertex buffer object id
  GLuint m_VBO;

public:
  VertexBuffer() {
    LOGTRACEN;
    glGenBuffers(1, &m_VBO);
  };

  void bind() {
    LOGTRACEN;
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  }

  void setData(std::vector<Vertex> verticies) {
    LOGTRACEN;
    bind();
    glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(Vertex),
                 verticies.data(), GL_STATIC_DRAW);
  }
};

class ElementBuffer {
  /// @brief Element buffer object id
  GLuint m_EBO;

public:
  ElementBuffer() {
    LOGTRACEN;
    glGenBuffers(1, &m_EBO);
  };

  void bind() {
    LOGTRACEN;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
  };

  void setData(std::vector<GLuint> inicies) {
    bind();
    LOGTRACEN;
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, inicies.size() * sizeof(GLint),
                 inicies.data(), GL_STATIC_DRAW);
  }
};

class BasicMesh {
public:
  using verticies_t = std::vector<Vertex>;
  using indicies_t = std::vector<GLuint>;

private:
  /// @brief Vertex array object.
  VertexArray *m_VAO{nullptr};

  VertexBuffer *m_VBO{nullptr};

  ElementBuffer *m_EBO{nullptr};
  /// @biref Vericies collection.
  verticies_t m_verticies;
  /// @brief Elements  inidcies collection.
  indicies_t m_indicies;

protected:
  /**
   *@brief
   *
   * Because openGL vertex attrib pointers are set all shaders have to use same
   * layout.
   * */
  void initialize(verticies_t veritices, indicies_t indicies) {
    LOGTRACEN;
    if (veritices.empty()) {
      LOGWARN << "Empty verticies";
    }
    m_verticies = veritices;

    if (indicies.empty()) {
      LOGWARN << "Empty indicies";
    }
    m_indicies = indicies;

    m_VAO = new VertexArray{};

    m_VBO = new VertexBuffer{};
    m_EBO = new ElementBuffer{};

    m_VAO->bind();

    m_VBO->setData(m_verticies);
    m_EBO->setData(m_indicies);

    // setup attrib pointers
    m_VAO->setAttribPointer(0, 3, offsetof(Vertex, m_position));
    m_VAO->setAttribPointer(1, 3, offsetof(Vertex, m_normal));
    m_VAO->setAttribPointer(2, 2, offsetof(Vertex, m_texCord));
  }

public:
  BasicMesh(){};
  BasicMesh(verticies_t veritices, indicies_t indicies) {
    LOGTRACEN;
    initialize(veritices, indicies);
  }

  ~BasicMesh() { delete m_VAO; }

  void drawElements(Shader &shader) {
    shader.use();
    m_VAO->bind();
    glDrawElements(GL_TRIANGLES, m_indicies.size(), GL_UNSIGNED_INT, 0);
    m_VAO->unBind();
  }
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

  // VertexArray VAO{};
  // VAO.bind();

  // VertexBuffer VBO{};
  // VBO.setData(verticies);

  // ElementBuffer EBO{};
  // EBO.setData(indicies);

  // VAO.setAttribPointer(0, 3, offsetof(Vertex, m_position));

  // VAO.unBind();

  BasicMesh rectangle{verticies, indicies};

  engine.setLoopFunction([&]() {
    glClearColor(0.0, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    rectangle.drawElements(shader);
  });

  engine.loop();
}
