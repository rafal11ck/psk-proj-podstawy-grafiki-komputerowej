
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "engine.hpp"
#include "mesh.hpp"
#include "shader.hpp"
#include "vertex.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/fwd.hpp>
#include <vector>

#define TRACE
#include "log.hpp"

#include <camera.hpp>

#include <resources.hpp>

Engine &engine{Engine::getInstance()};

Camera camera{{0.f, 0.f, 3.f}};

Shader ourShader("vertex.glsl", "fragment.glsl");

void init();
void loopFun();
void cameraMouseHandle(const sf::Event ev);

namespace cube {
// clang-format off

  std::vector<Vertex> data[] {
  {
  Vertex{{-0.5f, -0.5f, -0.5f},  {0.0f,  0.0f, -1.0f}, {0.0f, 0.0f}}
/**
,{0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f}

,{0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f}

,{0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f}

,{-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f}

,{-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f}


,{-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f}

,{0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f}

,{0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f}

,{0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f}

,{-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f}

,{-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f}


,{-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f}

,{-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f}

,{-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f}

,{-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f}

,{-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f}

,{-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f}


,{0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f}

,{0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f}

,{0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f}

,{0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f}

,{0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f}

,{0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f}


,{-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f}

,{0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f}

,{0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f}

,{0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f}

,{-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f}

,{-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f}


,{-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f}

,{0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f}

,{0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f}

,{0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f}

,{-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f}

,{-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f}
*/
}
};

    std::vector<unsigned int>indicies {{}};

// clang-format on
}; // namespace cube

int main() {
  LOGTRACEN;

  init();
  std::cout << "Init done\n";

  engine.setLoopFunction(loopFun);
  engine.loop();
}

void init() {

  LOGINFO << getResourcesPath() << '\n';
  LOGINFO << getResourcesPath() << '\n';

  camera.m_movementSpeed = 250;

  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  // stbi_set_flip_vertically_on_load(true);

  engine.setMaxFps(75);
}

void loopFun() {

  // handleCamera();

  glClearColor(0.0, 0.2f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // pass projection matrix to shader (note that in this case it could change
  // every frame)
  glm::mat4 projection =
      glm::perspective(glm::radians(camera.m_zoom),
                       static_cast<float>(engine.getWindow().getSize().x) /
                           static_cast<float>(engine.getWindow().getSize().y),
                       0.1f, 100.0f);

  glm::mat4 view = camera.getViewMatrix();

  ourShader.setMat4("projection", view);
  ourShader.setMat4("view", view);

  glm::mat4 model = glm::mat4(1.0f);
  // model = glm::translate(model, glm::vec3(0.f, 0.f, 0.f));
  // model = glm::scale(model, glm::vec3(1.f, 1.0f, 1.0f));
  ourShader.setMat4("model", model);
}
