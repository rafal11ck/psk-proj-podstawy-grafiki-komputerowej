#ifndef CUBE_HPP_
#define CUBE_HPP_

#include "GL/glew.h"
#include "shape.hpp"
#include "texture.hpp"

class Cube final : public Shape {
  static const std::vector<Vertex> s_verticies;
  static const std::vector<GLuint> s_indicies;

public:
  Cube(Texture textureDiffuse = Texture{Texture::TextureType::diffuse},
       Texture textureSpecular = Texture{Texture::TextureType::specular});
};

#endif // CUBE_HPP_
