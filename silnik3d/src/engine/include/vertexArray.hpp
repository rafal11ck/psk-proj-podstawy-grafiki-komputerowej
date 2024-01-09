#ifndef VERTEXARRAY_HPP_
#define VERTEXARRAY_HPP_

#include <GL/glew.h>

class VertexArray final {
private:
  GLuint m_id;

public:
  VertexArray();
  ~VertexArray();

  void setAttribPointer(GLuint layout, GLuint numOfValues, GLuint pointerVal);
  void bind();
  void unbind();
  void drawVertices(GLsizei numOfVertices, GLenum primitive = GL_TRIANGLES);
  void drawIndices(GLsizei numOfIndices, GLenum primitive = GL_TRIANGLES);
};

#endif // VERTEXARRAY_HPP_
