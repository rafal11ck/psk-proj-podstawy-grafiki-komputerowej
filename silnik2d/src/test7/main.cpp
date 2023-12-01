#include "SFML/Graphics/RectangleShape.hpp"
#include "engine.hpp"
#include <iostream>

// This is example of transformation usate.
// Consider using AnimatedObject class if you want to do animations based on
// time elapsed

sf::RectangleShape *rect = new sf::RectangleShape({100, 100});

void customLoop() {
  static float dt{};
  dt += Engine::getInstance().getLastFrameDuration().asSeconds();

  // after some time execute step
  if (dt < 0.3)
    return;

  dt = 0;
  static int step{};

  // each second do one of following
  switch (step) {
    // step 0 move right by 100
  case 0:
    rect->move(100, 0);
    ++step;
    break;
  case 1:
    // make rectangle 2 times bigger
    rect->scale(2, 2);
    ++step;
    break;
  case 2:
    // rotate it
    // Check SFML documentation
    rect->setOrigin(rect->getSize().x / 2, rect->getSize().y / 2);

    // rotate by 45 degress
    rect->rotate(45);
    ++step;
    break;

  case 3:
    // Shrink it
    rect->scale(0.5, 0.5);
    ++step;
    break;
  case 4:
    // Move it to starting position
    rect->move(-100, 0);
    ++step;
    break;

  default:
    // reset step
    step = 0;
  }
}

int main() {
  Engine &eng = Engine::getInstance().setWindowTitle("dev").buildWindow();

  rect->setPosition(100, 300);

  eng.add(rect);

  eng.setLoopFunction(customLoop);

  eng.loop();
}
