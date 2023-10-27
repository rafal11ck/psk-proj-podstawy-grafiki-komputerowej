#include "SFML/Graphics/Color.hpp"
#include "SFML/Window/Event.hpp"
#include "circle.hpp"
#include "engine.hpp"
#include "point2d.hpp"
#include <algorithm>
#include <iostream>

#include "lineSegment.hpp"

void customLoopFunction() {}

void addSomeRenderables() {
  Engine &eng = Engine::getInstance();

  LineSegment *l =
      new LineSegment{{70 + 85, 10}, {70 + 85, 120}, sf::Color::Yellow};
  eng.add(l);

  Circle *circle{new Circle{}};
  circle->setRadius(45).setPosition({70, 100}).setFillColor(sf::Color::Yellow);
  eng.add(circle);

  Circle *circle2{new Circle{}};
  circle2->setRadius(45)
      .setPosition({150, 100})
      .setFillColor(sf::Color::Yellow);
  eng.add(circle2);
}

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
                    .setMaxFps(30)
                    .setLoopFunction(customLoopFunction)
                    .buildWindow();

  setUpCustomEvents();
  addSomeRenderables();

  eng.loop();
}
