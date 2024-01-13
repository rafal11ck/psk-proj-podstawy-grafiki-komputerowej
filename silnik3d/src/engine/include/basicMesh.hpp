#ifndef BASICMESH_HPP_
#define BASICMESH_HPP_

#include "drawable.hpp"
#include "elementBuffer.hpp"
#include "log.hpp"
#include "moveable.hpp"
#include "rotatable.hpp"
#include "shader.hpp"
#include "vertexArray.hpp"
#include "vertexBuffer.hpp"
#include <GL/glew.h>
#include <netdb.h>

class BasicMesh : public Drawable {
public:
  using verticies_t = std::vector<Vertex>;
  using indicies_t = std::vector<GLuint>;

protected:
  /// @brief Vertex array object.
  VertexArray *m_VAO{nullptr};

private:
  VertexBuffer *m_VBO{nullptr};

  ElementBuffer *m_EBO{nullptr};
  /// @brief Vericies collection.
  verticies_t m_verticies;
  /// @brief Elements  inidcies collection.
  indicies_t m_indicies;

protected:
  /**
   *@brief
   *
   * Because openGL vertex attrib pointers are set all shaders have to use same
   * layout.
   * */
  void initialize(verticies_t veritices, indicies_t indicies);

public:
  BasicMesh();
  BasicMesh(verticies_t veritices, indicies_t indicies);

  ~BasicMesh();

  virtual void draw(Shader &shader) override;
};
#endif // BASICMESH_HPP_
