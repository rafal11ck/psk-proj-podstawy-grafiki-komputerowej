#ifndef TRANSFORMABLE_HPP_
#define TRANSFORMABLE_HPP_

/**
 *@brief Enables to do transformations to used as model matrix.
 **/
#include <glm/glm.hpp>

class Transformable {
protected:
  /**
   *@brief Model matrix.
   **/
  // glm::vec4 m_model{1.0f};

  virtual glm::vec4 getModel() = 0;
  virtual ~Transformable() = 0;
};

#endif // TRANSFORMABLE_HPP_
