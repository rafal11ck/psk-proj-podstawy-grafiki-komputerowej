
/**
 *@file
 *@brief Test shapes.
 **/

#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "cube.hpp"
#include "engine.hpp"
#include "resources.hpp"
#include "sphere.hpp"
#include "texture.hpp"
#include "torus.hpp"

Engine &engine{Engine::getInstance()};

int main() {
  engine.setProjectionType(Engine::ProjectionType::perspective);
  engine.setCameraHandlingKeyboard(true);
  engine.setCameraHandlingMouse(true);
  engine.getWindow().setMouseCursorGrabbed(true);
  engine.getWindow().setMouseCursorVisible(false);

  engine.setEventHandler(Engine::Event::KeyReleased, [](sf::Event ev) {
    static bool wireOn{false};
    if (ev.key.code == sf::Keyboard::Key::M) {
      LOGINFO << "Switching wireframe mode " << wireOn << '\n';
      engine.setWireframeMode(wireOn = !wireOn);
    }
  });

  engine.setMaxFps(75);

  Shape *boxContainer =
      new Cube{Texture{Texture::TextureType::diffuse,
                       getResourcesPath() + "/textures/container.png"},
               Texture{Texture::TextureType::specular,
                       getResourcesPath() + "/textures/eureka.png"}};

  boxContainer->setPosition(-3, 0, -3);
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
  boxMemeFast->setPosition(-3, 1, -3.5);
  boxMemeFast->setScale(0.3);
  engine.addDrawable(boxMemeFast);

  Shape *ball =
      new Sphere(1, Texture{Texture::TextureType::diffuse,
                            getResourcesPath() + "/textures/ball.png"});
  engine.addDrawable(ball);
  ball->setScale(0.3);

  Shape *paczek{new Torus(0.1, 1,
                          {Texture::TextureType::diffuse,
                           getResourcesPath() + "textures/container.png"},
                          {Texture::TextureType::specular}, 100, 100)};

  engine.addDrawable(paczek);

  ball->setPosition({0, 0, -5});
  paczek->setPosition({0, 0, -5});

  engine.setLoopFunction([&]() {
    engine.moveMouseToCenterOfWindow();
    static constexpr float angleSpeed{60};

    const float rotation{
        glm::radians(angleSpeed * engine.getLastFrameDuration().asSeconds())};

    paczek->rotate(rotation * 2, {1, 0, 1});
    ball->rotate(rotation, {-0.5, 1, 0});
    boxContainer->rotate(rotation, {1, 0, 0});
    boxMeme->rotate(rotation, {-1, 0, 0});
    boxMemeFast->rotate(rotation * 5, {0, 0.5, 0.5});
  });

  engine.loop();
}
