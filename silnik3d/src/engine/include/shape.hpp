#ifndef SHAPE_HPP_
#define SHAPE_HPP_

#include "mesh.hpp"
#include "vertex.hpp"
#include <glm/glm.hpp>
#include <vector>

class Shape : public Mesh {
protected:
  glm::vec3 m_color;

  virtual void populateVertices();
  virtual void populateIndices();

public:
  Shape(std::vector<Vertex> &vertices, std::vector<GLuint> &indices);

  virtual ~Shape() = 0;
};

#endif // SHAPE_HPP_
