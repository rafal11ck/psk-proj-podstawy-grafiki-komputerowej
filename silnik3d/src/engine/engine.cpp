#include "SFML/Window/ContextSettings.hpp"
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <iostream>

const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

int main() {

  std::cout << "Hi\n";
  sf::ContextSettings settings{24, 8, 4, 3, 3, settings.Core};

  // create the window
  sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default,
                    settings);
  window.setVerticalSyncEnabled(true);

  // activate the window
  window.setActive(true);

  glewInit();

  // load resources, initialize the OpenGL states, ...
  // build and compile our shader program
  // ------------------------------------
  // vertex shader

  std::cout << "Hi1.1\n";
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

  std::cout << "Hi2\n";
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  // check for shader compile errors
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }
  // fragment shader
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  // check for shader compile errors
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }
  // link shaders
  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  // check for linking errors
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << infoLog << std::endl;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------
  float verticesA[] = {
      -0.8f, 0.0f,
      0.0f, // ll
      -0.4f, 0.8f,
      0.0f, // lt
      0.0f,  -0.0f,
      0.0f // center
  };

  float verticesB[] = {
      0.0f, -0.0f,
      0.0f, // center
      0.8f, 0.0f,
      0.0f, // rr
      0.4,  0.8,
      0.0f // rt
  };

  unsigned int VAOs[2];
  glGenVertexArrays(2, VAOs);
  unsigned int VBOs[2];
  glGenBuffers(2, VBOs);

  glBindVertexArray(VAOs[0]);
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verticesA), verticesA, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);

  glBindVertexArray(VAOs[1]);
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verticesB), verticesB, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);

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

    // draw...

    glUseProgram(shaderProgram);
    // seeing as we only have a single VAO there's no need to bind it
    // every time, but we'll do so to keep things a bit more organized
    glBindVertexArray(VAOs[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(VAOs[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // glBindVertexArray(0);

    // end the current frame (internally swaps the front and back buffers)
    window.display();
  }

  // release resources...
  // optional: de-allocate all resources once they've outlived their purpose:
  // ------------------------------------------------------------------------
  glDeleteVertexArrays(2, VAOs);
  glDeleteBuffers(2, VBOs);
  glDeleteProgram(shaderProgram);

  return 0;
}
