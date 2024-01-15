#ifndef SHAPE_HPP_
#define SHAPE_HPP_

#include "basicMesh.hpp"
#include "rotatable.hpp"
#include "scaleable.hpp"
#include "texture.hpp"

class Shape : public BasicMesh,
              public virtual Movable,
              public virtual Rotatable,
              public virtual Scalable {

public:
  Shape(verticies_t verticies, indicies_t indicies,
        Texture textureDiffuse = Texture{Texture::TextureType::diffuse});

  virtual glm::mat4 getModelMatrix() override;

  virtual void draw(Shader &shader) override;

  virtual ~Shape() override;

private:
  Texture m_textureDiffuse;
};

#endif // SHAPE_HPP_
