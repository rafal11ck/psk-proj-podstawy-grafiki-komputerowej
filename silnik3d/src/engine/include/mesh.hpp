#ifndef MESH_HPP_
#define MESH_HPP_

#include "drawable.hpp"
#include "movable.hpp"
#include "rotateable.hpp"
#include "scaleable.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "vertex.hpp"
#include "vertexArray.hpp"

#include <vector>

class Mesh : public Drawable,
             public Scalable,
             public Rotatable,
             public Movable {
protected:
  std::vector<Vertex> m_vertices;
  std::vector<GLuint> m_indices;
  VertexArray m_vao;
  Texture m_diffuse;
  Texture m_specular;
  GLfloat m_shininess;

public:
  Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices);
  ~Mesh();

  void setDiffuseTexture(const char *path);
  void setSpecularTexture(const char *path);
  void setShininess(GLfloat shininess);

  Texture *getDiffuseTexture();
  Texture *getSpecularTexture();
  GLfloat getShininess();

  void initialize();
  void draw(Shader &shader) override;
};

#endif
