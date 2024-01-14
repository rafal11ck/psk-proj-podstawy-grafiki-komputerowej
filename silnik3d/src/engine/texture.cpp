#include <cstdlib>
#define TRACE
#include "log.hpp"
#include "resources.hpp"
#include "texture.hpp"
#include <stb/stb_image.h>

const std::string Texture::defaultTexturePath{getResourcesPath() +
                                              "textures/default.png"};

void Texture::loadImage(const char *path) {
  LOGTRACEN;
  stbi_set_flip_vertically_on_load(true);

  int width, height, nrChannels;
  unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 3);

  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    LOGERROR << "Failed to load texture from path " << m_path << "\n";
  }

  stbi_image_free(data);
}

Texture::Texture(TextureType type, const std::string &path, GLenum wrapping)
    : m_type(type), m_wrapping(wrapping), m_path(path) {
  LOGTRACEN;
  initialize();
}

void Texture::initialize() {
  LOGTRACEN;
  glGenTextures(1, &m_id);
  // bind();

  glBindTexture(GL_TEXTURE_2D, m_id);

  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                  static_cast<GLint>(m_wrapping));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                  static_cast<GLint>(m_wrapping));
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  loadImage(m_path.c_str());
  unbind();
}

Texture::~Texture() { glDeleteTextures(1, &m_id); }

void Texture::bind() {
  LOGTRACEN;
  GLenum textureToActivate{};
  switch (m_type) {
  case diffuse:
    textureToActivate = GL_TEXTURE0;
    break;
  case specular:
    textureToActivate = GL_TEXTURE1;
    break;
  default:
    LOGERROR << "Unknwon texture type (casted = " << static_cast<int>(m_type)
             << ")\n";
    std::abort();
    break;
  }
  glActiveTexture(textureToActivate);
  glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::unbind() { glBindTexture(GL_TEXTURE_2D, 0); }

GLuint Texture::getId() const { return m_id; };
