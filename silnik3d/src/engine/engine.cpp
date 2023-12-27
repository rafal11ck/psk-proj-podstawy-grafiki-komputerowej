#include "engine.hpp"
#include <GL/glew.h>
#include <iostream>

Engine &Engine::buildWindow(sf::ContextSettings settings) {
  // create the window
  m_window.create(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default,
                  settings);

  m_window.setVerticalSyncEnabled(true);

  // activate the window
  m_window.setActive(true);

  // Opengl extension load
  glewInit();

  return *this;
}

void Engine::loop() {
  // run the main loop
  isLoopRunning = true;
  while (isLoopRunning) {

    // handle events
    handleEvents();

    // render
    // ------

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //  end the current frame (internally swaps the front and back buffers)
    m_window.display();
  }
}

void Engine::handleEvents() {
  sf::Event event;
  while (m_window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      // end the program
      isLoopRunning = false;
    } else if (event.type == sf::Event::Resized) {
      // adjust the viewport when the window is resized
      glViewport(0, 0, event.size.width, event.size.height);
    }
  }
}
