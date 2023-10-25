#include "SFML/Graphics/Color.hpp"
#include "SFML/Window/Event.hpp"
#include "engine.hpp"
#include "point2d.hpp"
#include "primitiveRenderer.hpp"
#include <algorithm>
#include <iostream>

void customLoopFunction() {
  PrimitiveRenderer::drawLine({20, 170}, {200, 170}, sf::Color::Magenta);

  PrimitiveRenderer::drawCircle({100, 270}, 70);
  PrimitiveRenderer::drawEclipse({200, 400}, 140, 70);
  PrimitiveRenderer::drawEclipse({200, 400}, 40, 60);
  PrimitiveRenderer::fill({150, 400}, sf::Color::Blue,
                          PrimitiveRenderer::s_defaultColor);
}

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

  eng.loop();
}
