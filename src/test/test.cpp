#include "SFML/Graphics/Color.hpp"
#include "SFML/Window/Event.hpp"
#include "circleShape.hpp"
#include "drawable.hpp"
#include "engine.hpp"
#include "point2d.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

#include "lineSegment.hpp"
#include "primitiveRenderer.hpp"
#include "rectangleShape.hpp"

std::vector<Shape *> drawables;

void customLoopFunction() {
  static float speed = 200;
  static float distanceSum = 0;

  auto deltaTime{Engine::getInstance().getLastFrameDuration().asSeconds()};

  float distance = speed * deltaTime;
  distanceSum += std::abs(distance);
  // std::cerr << "Elapsed " << deltaTime << '\t' << "Sum " << distanceSum <<
  // '\n';

  for (auto drawable : drawables) {
    drawable->setPosition(drawable->getPosition() + Point2d{0, distance});
  }

  if (distanceSum >= 500) {
    speed *= -1;
    distanceSum = 0;
  }
}

void addSomeRenderables() {
  Engine &eng = Engine::getInstance();

  CircleShape *circle{new CircleShape{}};
  circle->setRadius(45).setPosition({70, 150}).setFillColor(sf::Color::Yellow);
  drawables.push_back(circle);
  eng.add(circle);

  CircleShape *circle2{new CircleShape{}};
  circle2->setRadius(45)
      .setPosition({160, 150})
      .setFillColor(sf::Color::Yellow);
  drawables.push_back(circle2);
  eng.add(circle2);

  float thickness = 20;
  RectangleShape *recangle1 = new RectangleShape{
      {70 + 45 * 2 - thickness / 2, 50}, {thickness, 170}, sf::Color::Yellow};

  drawables.push_back(recangle1);
  eng.add(recangle1);
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
                    .setMaxFps(60)
                    .setLoopFunction(customLoopFunction)
                    .buildWindow();

  setUpCustomEvents();
  addSomeRenderables();
  eng.setLoopFunction(customLoopFunction);
  eng.loop();
}
