#ifndef ROTATABLE_HPP_
#define ROTATABLE_HPP_

#include "transformable.hpp"
#include <GL/glew.h>
#include <glm/glm.hpp>

/// @brief Indicates that object is rotateable
class Rotatable : virtual public Transformable {
private:
  /// @brief Rotation Matrix
  glm::mat4 m_rotationMatrix{1.f};

public:
  /**
   *@brief Rotate by given angle around axis.
   *@param angle Angle in radians
   **/
  void rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);

  /**
   *@brief Rotate by given angle around axis.
   *@param angle Angle in radians
   **/
  void rotate(GLfloat angle, glm::vec3 axis);

  /// @brief Rotation Matrix getter
  /// @return Retursn the Rotation Matrix
  const glm::mat4 &getRotationMatrix() const;
};

#endif // ROTATABLE_HPP_
