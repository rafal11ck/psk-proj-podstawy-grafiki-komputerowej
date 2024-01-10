#include "mesh.hpp"

#include "elementBuffer.hpp"
#include "vertexBuffer.hpp"

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices) {
  this->m_vertices = vertices;
  this->m_indices = indices;
}

void Mesh::initialize() {
  VertexBuffer vbo;
  ElementBuffer ebo;
  m_vao = new VertexArray;

  m_vao->bind();
  vbo.bind();
  ebo.bind();

  vbo.setData(m_vertices);
  ebo.setData(m_indices);

  m_vao->setAttribPointer(0, 3, 0);
  m_vao->setAttribPointer(1, 3, offsetof(Vertex, m_normal));
  m_vao->setAttribPointer(2, 2, offsetof(Vertex, m_texCoords));

  m_vao->unbind();
  vbo.unbind();
  ebo.unbind();

  m_diffuse->initialize();
  m_specular->initialize();
}

Mesh::~Mesh() {
  delete m_diffuse;
  delete m_specular;
}

void Mesh::setDiffuseTexture(const char *path) {
  m_diffuse = new Texture(Texture::DIFFUSE, path);
}

void Mesh::setSpecularTexture(const char *path) {
  m_specular = new Texture(Texture::SPECULAR, path);
}

void Mesh::setShininess(GLfloat shininess) { this->m_shininess = shininess; }

Texture *Mesh::getDiffuseTexture() { return m_diffuse; }

Texture *Mesh::getSpecularTexture() { return m_specular; }

GLfloat Mesh::getShininess() { return m_shininess; }

void Mesh::draw(Shader &shader) {
  m_vao->bind();
  m_diffuse->bind();
  m_specular->bind();

  shader.use();
  shader.setMat4("model", m_model);
  shader.setInt("material.diffuse", 0);
  shader.setInt("material.specular", 1);
  shader.setFloat("material.shininess", m_shininess);

  m_vao->drawIndices(m_indices.size());
}
