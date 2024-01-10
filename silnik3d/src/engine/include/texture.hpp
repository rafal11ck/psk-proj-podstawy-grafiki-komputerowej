#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_
#include <GL/glew.h>
#include <iostream>
#include <resources.hpp>
#include <string>

class Texture {
public:
  using TextureType = enum TEXTURE { DIFFUSE, SPECULAR };

private:
  TextureType type;
  GLuint id;
  GLenum wrapping;
  std::string path;

  void loadImage(const char *path);

public:
  Texture(TextureType type = DIFFUSE,
          std::string = (std::string(getResourcesPath()) +
                         "/textures/default.png"),
          GLenum wrapping = GL_REPEAT);
  ~Texture();

  void initialize();
  void bind();
  void unbind();
};
#endif // TEXTURE_HPP_
