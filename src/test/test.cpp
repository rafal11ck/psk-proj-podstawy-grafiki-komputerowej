#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Shape.hpp"
#include "SFML/Window/Event.hpp"
#include "engine.hpp"
#include "point2d.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

#include "lineSegment.hpp"
#include "primitiveRenderer.hpp"
#include "rectangleShape.hpp"

namespace G {
std::vector<Engine::Shape *> drwables{};
bool moveVertically{false};
}; // namespace G

void customLoopFunction() {
  static float speed = 500;
  static float distanceSum = 0;

  auto deltaTime{Engine::getInstance().getLastFrameDuration().asSeconds()};

  float distance = speed * deltaTime;
  distanceSum += std::abs(distance);

  for (Engine::Shape *i : G::drwables) {
    if (G::moveVertically)
      i->move(distance, 0);
    else {
      i->move(0, distance);
    }
  }

  if (distanceSum >= 500) {
    speed *= -1;
    distanceSum = 0;
  }
}

void addSomeRenderables() {
  Engine &eng = Engine::getInstance();
  const sf::Color pink{0xff, 0x69, 0xb4};

  for (int i{}; i < 8; ++i) {
    sf::CircleShape *circle =
        new sf::CircleShape{10 + static_cast<float>(i) * 4};
    circle->setPosition(50 + i * 100, 100 - static_cast<float>(i) * 4);
    circle->setFillColor(pink);
    eng.add(circle);
    G::drwables.push_back(circle);
  };

  sf::RectangleShape *rectangle{new sf::RectangleShape{{8 * 100 + 50, 4}}};
  rectangle->setPosition({50 + 5, 100 + 10});
  rectangle->setFillColor(pink);
  eng.add(rectangle);
  G::drwables.push_back(rectangle);
}

void setUpCustomEvents() {
  Engine::getInstance().setEventHandler(
      sf::Event::MouseButtonPressed, [](const sf::Event &ev) {
        std::cout << "Custom event handler Mouse button press "
                  << ev.mouseButton.button << '\t' << ev.mouseButton.x << '\t'
                  << ev.mouseButton.y << "\n";
        if (ev.mouseButton.button == 0)
          G::moveVertically = !G::moveVertically;
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
