#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Color.hpp"
#include "engine.hpp"
#include <cstdlib>
#include <iostream>
#include <random>

sf::CircleShape *circle = new sf::CircleShape(100);

void customLoop() {
  // count to second
  static float dt{};
  dt += Engine::getInstance().getLastFrameDuration().asSeconds();

  // Do not change color if less then scond elapsed.
  if (dt < 1)
    return;
  dt = 0;

  // Set color based on random RGB values
  sf::Color randomColor{static_cast<sf::Uint8>(rand() % 265),
                        static_cast<sf::Uint8>(rand() % 256),
                        static_cast<sf::Uint8>(rand() % 256)};
  // Set fill color
  circle->setFillColor(randomColor);
}

int main() {
  // initalize random number generator in order to randomize colors.
  srand(time(0));

  Engine &eng =
      Engine::getInstance().setMaxFps(75).setWindowTitle("dev").buildWindow();

  circle->setPosition(100, 100);

  // set custom loop function to change color.
  eng.setLoopFunction(customLoop);

  eng.add(circle);

  eng.loop();
}
