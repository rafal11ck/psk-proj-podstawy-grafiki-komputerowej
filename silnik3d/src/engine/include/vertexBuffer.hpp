#ifndef VERTEXBUFFER_HPP_
#define VERTEXBUFFER_HPP_

#include "vertex.hpp"
#include <GL/glew.h>
#include <vector>

class VertexBuffer {
private:
  GLuint id;

public:
  VertexBuffer();
  ~VertexBuffer();

  void setData(std::vector<Vertex> &vertices, GLenum usage = GL_STATIC_DRAW);
  void bind();
  void unbind();
};

#endif // VERTEXBUFFER_HPP_
