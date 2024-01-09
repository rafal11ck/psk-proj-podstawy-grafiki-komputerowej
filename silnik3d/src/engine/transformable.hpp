#ifndef TRANSFORMABLE_HPP_
#define TRANSFORMABLE_HPP_

#include <glm/glm.hpp>

/**
 *@brief
 *
 * Enables to do transformations
 **/
class Transformable {
protected:
  /**
   *@brief Model transformation matrix.
   **/
  glm::mat4 m_model{1.0f};

public:
  Transformable();
};

#endif // TRANSFORMABLE_HPP_
