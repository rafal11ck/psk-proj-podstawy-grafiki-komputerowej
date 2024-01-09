#ifndef CUBE_HPP_
#define CUBE_HPP_

#include "shape.hpp"

class Cube : public Shape {

protected:
  void populateVertices() override;
  void populateIndices() override;

public:
  Cube();
};

#endif // CUBE_HPP_
