#include "SFML/Graphics/Color.hpp"
#include "SFML/Window/Event.hpp"
#include "engine.hpp"
#include "point2d.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

#include "lineSegment.hpp"
#include "primitiveRenderer.hpp"
#include "rectangleShape.hpp"

void customLoopFunction() {
  static float speed = 200;
  static float distanceSum = 0;

  auto deltaTime{Engine::getInstance().getLastFrameDuration().asSeconds()};

  float distance = speed * deltaTime;

  if (distanceSum >= 500) {
    speed *= -1;
    distanceSum = 0;
  }
}

void addSomeRenderables() { Engine &eng = Engine::getInstance(); }

void setUpCustomEvents() {
  Engine::getInstance().setEventHandler(
      sf::Event::MouseButtonPressed, [](const sf::Event &ev) {
        std::cout << "Custom event handler Mouse button press "
                  << ev.mouseButton.button << '\t' << ev.mouseButton.x << '\t'
                  << ev.mouseButton.y << "\n";
      });
}

int main() {
  Engine &eng = Engine::getInstance()
                    .setWindowTitle("dev")
                    .setMaxFps(60)
                    .setLoopFunction(customLoopFunction)
                    .buildWindow();

  setUpCustomEvents();
  addSomeRenderables();
  eng.setLoopFunction(customLoopFunction);
  eng.loop();
}
