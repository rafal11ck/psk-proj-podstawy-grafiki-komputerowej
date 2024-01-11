#ifndef ELEMENTBUFFER_HPP_
#define ELEMENTBUFFER_HPP_

#include <GL/glew.h>
#include <vector>

class ElementBuffer {
  /// @brief Element buffer object id
  GLuint m_EBO;

public:
  ElementBuffer();

  void bind();

  void setData(std::vector<GLuint> inicies);
};

#endif // ELEMENTBUFFER_HPP_
