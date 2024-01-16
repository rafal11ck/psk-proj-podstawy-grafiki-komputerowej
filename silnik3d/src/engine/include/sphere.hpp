#ifndef SPHERE_HPP_
#define SPHERE_HPP_

#include "shape.hpp"
#include "vertex.hpp"
#include <GL/glew.h>

class Sphere : public Shape {
  static std::vector<Vertex> generateVerticies(float radius,
                                               GLuint sectorCount = 30,
                                               GLuint stackCount = 30);

  static std::vector<GLuint> generateIndicies(float radius,
                                              GLuint sectorCount = 30,
                                              GLuint stackCount = 30);
};

#endif // SPHERE_HPP_
