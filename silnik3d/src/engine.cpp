#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>

int main() {
  // create the window
  sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default,
                    sf::ContextSettings(32));
  window.setVerticalSyncEnabled(true);

  // activate the window
  window.setActive(true);

  // load resources, initialize the OpenGL states, ...

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

    // clear the buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw...

    GLuint vertexArrayId;
    glGenVertexArrays(1, &vertexArrayId);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(0.5f, -0.5f);
    glEnd();

    // end the current frame (internally swaps the front and back buffers)
    window.display();
  }

  // release resources...

  return 0;
}
