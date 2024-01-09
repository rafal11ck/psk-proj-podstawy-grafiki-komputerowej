#include "include/vertexBuffer.hpp"

VertexBuffer::VertexBuffer() { glGenBuffers(1, &m_id); }

void VertexBuffer::setData(std::vector<Vertex> &vertices, GLenum usage) {
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
               vertices.data(), usage);
}

VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &m_id); }

void VertexBuffer::bind() { glBindBuffer(GL_ARRAY_BUFFER, m_id); }

void VertexBuffer::unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }
