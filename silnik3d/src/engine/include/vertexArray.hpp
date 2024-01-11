#ifndef VERTEXARRAY_HPP_
#define VERTEXARRAY_HPP_

#include <GL/glew.h>

class VertexArray {
  /// @brief Vertex array id;
  GLuint m_VAOid{};

public:
  VertexArray();

  void bind();

  static void unBind();

  /**
   *@param layout layout number that shader uses to access data.
   *@param size How many values are in one struct ex. (*3* floats).
   *@param offset offset in values count. (use offsetof())
   **/
  void setAttribPointer(GLuint layout, GLuint size, GLuint offset = 0);
};
#endif // VERTEXARRAY_HPP_
