
/**
 *@file
 *@brief Test Cube.
 **/

#include "cube.hpp"
#include "engine.hpp"

Engine &engine{Engine::getInstance()};

int main() {
  engine.setProjectionType(Engine::ProjectionType::perspective);
  engine.setCameraHandlingKeyboard(true);
  engine.setCameraHandlingMouse(true);
  engine.getWindow().setMouseCursorGrabbed(true);
  engine.getWindow().setMouseCursorVisible(false);

  engine.setMaxFps(75);

  Shape *boxContainer =
      new Cube{Texture{Texture::TextureType::diffuse,
                       getResourcesPath() + "/textures/container.png"},
               Texture{Texture::TextureType::specular,
                       getResourcesPath() + "/textures/eureka.png"}};

  boxContainer->setPosition(-0.5, 0, -4);
  boxContainer->setScale(0.2);
  engine.addDrawable(boxContainer);

  Shape *boxMeme =
      new Cube(Texture{Texture::TextureType::diffuse,
                       getResourcesPath() + "/textures/eureka.png"});
  engine.addDrawable(boxMeme);
  boxMeme->setPosition(0, -1, -3);
  boxMeme->setScale(0.2);

  Shape *boxMemeFast =
      new Cube(Texture{Texture::TextureType::diffuse,
                       getResourcesPath() + "/textures/eureka.png"});
  boxMemeFast->setPosition(1, 1, -3.5);
  boxMemeFast->setScale(0.3);
  engine.addDrawable(boxMemeFast);

  engine.setLoopFunction([&]() {
    engine.moveMouseToCenterOfWindow();
    static constexpr float angleSpeed{60};
    const float rotation{
        glm::radians(angleSpeed * engine.getLastFrameDuration().asSeconds())};

    boxContainer->rotate(rotation, {1, 0, 0});
    boxMeme->rotate(rotation, {-1, 0, 0});
    boxMemeFast->rotate(rotation * 5, {0, 0.5, 0.5});
  });

  engine.loop();
}
