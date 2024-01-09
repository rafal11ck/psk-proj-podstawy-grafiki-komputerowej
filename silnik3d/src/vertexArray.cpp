#include "vertexArray.hpp"
#include "vertex.hpp"

VertexArray::VertexArray() { glGenVertexArrays(1, &m_id); }

VertexArray::~VertexArray() { glDeleteVertexArrays(1, &m_id); }

void VertexArray::bind() { glBindVertexArray(m_id); }

void VertexArray::unbind() { glBindVertexArray(0); }

void VertexArray::setAttribPointer(GLuint layout, GLuint numOfValues,
                                   GLuint pointerVal) {
  glVertexAttribPointer(layout, numOfValues, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        reinterpret_cast<void *>(pointerVal));
  glEnableVertexAttribArray(layout);
}

void VertexArray::drawVertices(GLsizei numOfVertices, GLenum primitive) {
  glDrawArrays(primitive, 0, numOfVertices);
}

void VertexArray::drawIndices(GLsizei numOfIndices, GLenum primitive) {
  glDrawElements(primitive, numOfIndices, GL_UNSIGNED_INT, 0);
}
