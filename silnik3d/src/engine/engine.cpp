// @clang-format off
#include <GL/glew.h>
// @clang-format on
#include "SFML/Window/ContextSettings.hpp"
#include "SFML/Window/Event.hpp"
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <iostream>

int main() {
  sf::ContextSettings settings{24, 8, 4, 3, 3, settings.Core};

  // create the window
  sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default,
                    settings);
  window.setVerticalSyncEnabled(true);

  // activate the window
  window.setActive(true);

  // Opengl extension load
  glewInit();

  // load resources, initialize the OpenGL states, ...
  // build and compile our shader program
  // ------------------------------------
  // vertex shader

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glLineWidth(5);

  // run the main loop
  bool running = true;
  while (running) {
    // handle events
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        // end the program
        running = false;
      } else if (event.type == sf::Event::Resized) {
        // adjust the viewport when the window is resized
        glViewport(0, 0, event.size.width, event.size.height);
      }
    }

    // color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    // clear the buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // end the current frame (internally swaps the front and back buffers)
    window.display();
  }

  // release resources...
  // optional: de-allocate all resources once they've outlived their purpose:
  // ------------------------------------------------------------------------

  return 0;
}
