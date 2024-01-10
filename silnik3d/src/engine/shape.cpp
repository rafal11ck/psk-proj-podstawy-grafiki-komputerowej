#include "shape.hpp"
#include "log.hpp"

Shape::Shape(std::vector<Vertex> &vertices, std::vector<GLuint> &indices)
    : Mesh(vertices, indices) {
  // if (vertices.empty())
  //   LOGWARN << "empty vertices\n";

  // if (indices.empty())
  //   LOGWARN << "empty indicies\n";

  this->m_color = glm::vec3(1.0, 1.0, 1.0f);
  this->m_vertices = vertices;
  this->m_indices = indices;
}

void Shape::populateVertices() { m_vertices = std::vector<Vertex>(); }

void Shape::populateIndices() { m_indices = std::vector<GLuint>(); }
