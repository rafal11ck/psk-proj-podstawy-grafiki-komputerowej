#ifndef BASICMESH_HPP_
#define BASICMESH_HPP_

#include "elementBuffer.hpp"
#include "log.hpp"
#include "shader.hpp"
#include "vertexArray.hpp"
#include "vertexBuffer.hpp"
#include <GL/glew.h>

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
  void initialize(verticies_t veritices, indicies_t indicies);

public:
  BasicMesh();
  BasicMesh(verticies_t veritices, indicies_t indicies);

  ~BasicMesh();

  void drawElements(Shader &shader);
};
#endif // BASICMESH_HPP_
