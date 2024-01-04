#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "SFML/Window/Event.hpp"
#include <SFML/OpenGL.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>

// An abstract camera class that processes input and calculates the
// corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera {

public:
  enum Camera_Movement { FORWARD, BACKWARD, LEFT, RIGHT };

  // Default camera values
  static constexpr float YAW = -90.0f;
  static constexpr float PITCH = 0.0f;
  static constexpr float SPEED = 2.5f;
  static constexpr float SENSITIVITY = 0.1f;
  static constexpr float ZOOM = 45.0f;

  // camera Attributes
  glm::vec3 m_position;
  glm::vec3 m_front;
  glm::vec3 m_up;
  glm::vec3 m_right;
  glm::vec3 m_worldUp;

  // euler Angles
  float m_yaw;
  float m_pitch;
  // camera options
  float m_movementSpeed;
  float m_mouseSensitivity;
  float m_zoom;

  // constructor with vectors
  Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
         glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW,
         float pitch = PITCH);

  // constructor with scalar values
  Camera(float posX, float posY, float posZ, float upX, float upY, float upZ,
         float yaw, float pitch);

  // returns the view matrix calculated using Euler Angles and the LookAt Matrix
  glm::mat4 GetViewMatrix();

  // processes input received from any keyboard-like input system. Accepts input
  // parameter in the form of camera defined ENUM (to abstract it from windowing
  // systems)
  void ProcessKeyboard(Camera_Movement direction, float deltaTime);

  // processes input received from a mouse input system. Expects the offset
  // value in both the x and y direction.
  void ProcessMouseMovement(float xoffset, float yoffset,
                            GLboolean constrainPitch = true);

  // processes input received from a mouse scroll-wheel event. Only requires
  // input on the vertical wheel-axis
  void ProcessMouseScroll(float yoffset);

  // calculates the front vector from the Camera's (updated) Euler Angles
  void updateCameraVectors();
};

#endif // CAMERA_HPP_
