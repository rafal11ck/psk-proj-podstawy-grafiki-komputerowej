#ifndef SHADER_HPP_
#define SHADER_HPP_

// @clang-format off
#include <GL/glew.h>
// @clang-format on
#include <SFML/OpenGL.hpp>
#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include <sstream>
#include <string>

/// @brief Shader class
class Shader {
private:
  using ShaderType = enum SHADER_TYPE { VERTEX, FRAGMENT };
  using Exception = enum EXCEPTION { COMPILE, LINK };
  GLuint fragmentShader;
  GLuint vertexShader;
  GLuint id;

  /// @brief Loads shader from file 
  std::string loadShaderFromFile(const char *path);
  GLuint createShader(const char *path, ShaderType type);
  GLuint createProgram();
  void checkForException(GLuint program, Exception exceptionType);

public:
  Shader(const char *vertexPath, const char *fragmentPath);
  Shader(const std::string vertexPath, const std::string fragmentPath);

  void use();
  void setBool(const std::string name, bool value);
  void setInt(const std::string name, int value);
  void setFloat(const std::string name, float value);
  void setVec2(const std::string name, const glm::vec2 &value);
  void setVec2(const std::string name, float x, float y);
  void setVec3(const std::string name, const glm::vec3 &value);
  void setVec3(const std::string name, float x, float y, float z);
  void setVec4(const std::string name, const glm::vec4 &value);
  void setVec4(const std::string name, float x, float y, float z, float w);
  void setMat2(const std::string name, const glm::mat2 &mat);
  void setMat3(const std::string name, const glm::mat3 &mat);
  void setMat4(const std::string name, const glm::mat4 &mat);
};

#endif // SHADER_HPP_
