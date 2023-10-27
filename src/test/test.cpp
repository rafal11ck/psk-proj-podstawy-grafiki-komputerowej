#include "SFML/Graphics/Color.hpp"
#include "SFML/Window/Event.hpp"
#include "engine.hpp"
#include "point2d.hpp"
#include <algorithm>
#include <iostream>

#include "lineSegment.hpp"

void customLoopFunction() {}

int main() {
  Engine &eng = Engine::getInstance()
                    .setWindowTitle("dev")
                    .setMaxFps(30)
                    .setLoopFunction(customLoopFunction)
                    .buildWindow();

  eng.setEventHandler(sf::Event::MouseButtonPressed, [](const sf::Event &ev) {
    std::cout << "Custom event handler Mouse button press "
              << ev.mouseButton.button << '\t' << ev.mouseButton.x << '\t'
              << ev.mouseButton.y << "\n";
  });

  LineSegment *l = new LineSegment{{10, 10}, {100, 200}, sf::Color::Yellow};
  eng.add(l);

  eng.loop();
}
