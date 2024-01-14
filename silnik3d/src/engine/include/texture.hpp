#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include <GL/glew.h>
#include <string>

class Texture {
public:
  enum TextureType { diffuse, specular };

  static const std::string defaultTexturePath;

private:
  TextureType m_type;
  GLuint m_id{0};
  GLenum m_wrapping;
  const std::string m_path{defaultTexturePath};

  void loadImage(const char *path);

  void initialize();

public:
  Texture(TextureType type, const std::string &path = defaultTexturePath,
          GLenum wrapping = GL_REPEAT);
  ~Texture();

  void bind();
  void unbind();

  GLuint getId() const;
};

#endif // TEXTURE_HPP_
