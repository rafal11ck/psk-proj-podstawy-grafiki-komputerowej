#ifndef VERTEX_HPP_
#define VERTEX_HPP_

#include <glm/glm.hpp>

struct Vertex {
  glm::vec3 m_position;
  glm::vec3 m_normal;
  glm::vec2 m_texCoords;
};

#endif // VERTEX_HPP_
