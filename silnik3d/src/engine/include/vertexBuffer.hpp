#ifndef VERTEXBUFFER_HPP_
#define VERTEXBUFFER_HPP_

#include "GL/glew.h"
#include "vertex.hpp"
#include <vector>

class VertexBuffer final {
private:
  GLuint m_id;

public:
  VertexBuffer();
  ~VertexBuffer();

  void setData(std::vector<Vertex> &verticies, GLenum usage = GL_STATIC_DRAW);
  void bind();
  void unbind();
};

#endif // VERTEXBUFFER_HPP_
