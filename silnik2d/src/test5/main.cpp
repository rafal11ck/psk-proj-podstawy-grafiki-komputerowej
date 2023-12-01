#include "SFML/Graphics/CircleShape.hpp"
#include "engine.hpp"
#include <iostream>

int main() {
  Engine &eng = Engine::getInstance().setWindowTitle("dev").buildWindow();

  sf::CircleShape *circle = new sf::CircleShape(100);

  circle->setPosition(100, 100);

  eng.add(circle);

  eng.loop();
}
