#ifndef VERTEX_HPP_
#define VERTEX_HPP_

#include <glm/glm.hpp>

struct Vertex {
  glm::vec3 m_position{0.f};
  glm::vec3 m_normal{0.f};
  glm::vec2 m_texCord{0.f};
};

#endif // VERTEX_HPP_
