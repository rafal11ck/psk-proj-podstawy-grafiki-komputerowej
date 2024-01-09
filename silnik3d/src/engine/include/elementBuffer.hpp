#ifndef ELEMENTBUFFER_HPP_
#define ELEMENTBUFFER_HPP_

#include "GL/glew.h"
#include <vector>

class ElementBuffer {
private:
  GLuint id;

public:
  ElementBuffer();
  ~ElementBuffer();

  void setData(std::vector<GLuint> &indices, GLenum usage = GL_STATIC_DRAW);
  void bind();
  void unbind();
};

#endif // ELEMENTBUFFER_HPP_
