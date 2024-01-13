#ifndef SHAPE_HPP_
#define SHAPE_HPP_

#include "basicMesh.hpp"
#include "rotatable.hpp"

class Shape : public BasicMesh,
              public virtual Movable,
              public virtual Rotatable {

public:
  Shape(verticies_t verticies, indicies_t indicies);

  virtual glm::mat4 getModelMatrix() override;

  virtual void draw(Shader &shader) override;

  virtual ~Shape() override;
};

#endif // SHAPE_HPP_
