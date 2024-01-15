#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include <GL/glew.h>
#include <string>

/**
 *@brief
 *
 *This class assumes texture unit 0 is used for diffuse texture and texture unit
 *1 is used for specular map.
 *
 *Remember to enable samplers by setting sampler2D uniforms.
 **/
class Texture {

public:
  enum class TextureType { diffuse, specular };

  static const std::string defaultTexturePath;

private:
  TextureType m_type;
  GLuint m_id;

public:
  /**
   *@brief Retuns corespnding texture unit for the type.
   **/
  static GLenum getTextureTypeUnit(const TextureType type);

  void bind();

  void unBind();

  // Only PNG / jpeg tested
  Texture(TextureType type, const std::string path = defaultTexturePath);
};
#endif // TEXTURE_HPP_
