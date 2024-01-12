#ifndef SHAPE_HPP_
#define SHAPE_HPP_

#include "basicMesh.hpp"
class Shape : public BasicMesh, public virtual Movable {

  virtual glm::vec4 getModelMatrix() override;
};

#endif // SHAPE_HPP_
