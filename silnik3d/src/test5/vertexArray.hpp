#ifndef VERTEXARRAY_HPP_
#define VERTEXARRAY_HPP_

class VertexArray {
  /// Vertex array id;
  GLuint m_VAOid{};

public:
  VertexArray() { glGenVertexArrays(1, &m_VAOid); }

  void bind(){glBindVertexArray(m_VAOid)};
};

#endif // VERTEXARRAY_HPP_
