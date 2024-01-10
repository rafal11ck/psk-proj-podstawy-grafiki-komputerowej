#ifndef MESH_HPP_
#define MESH_HPP_

#include "shader.hpp"
#include "texture.hpp"
#include "vertex.hpp"
#include <vector>

class Mesh {
public:
  // mesh data
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  std::vector<Texture> textures;

  Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
       std::vector<Texture> textures);

  void Draw(Shader &shader);

private:
  //  render data
  unsigned int VAO, VBO, EBO;

  void setupMesh();
};

#endif
