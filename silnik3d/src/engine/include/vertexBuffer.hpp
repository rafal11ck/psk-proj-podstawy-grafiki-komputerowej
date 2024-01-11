#ifndef VERTEXBUFFER_HPP_
#define VERTEXBUFFER_HPP_

#include "vertex.hpp"
#include <GL/glew.h>
#include <vector>

class VertexBuffer {
  /// @brief Vertex buffer object id
  GLuint m_VBO;

public:
  VertexBuffer();

  void bind();

  void setData(std::vector<Vertex> verticies);
};

#endif // VERTEXBUFFER_HPP_
