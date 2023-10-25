#include "SFML/Graphics/Color.hpp"
#include "SFML/Window/Event.hpp"
#include "engine.hpp"
#include "primitiveRenderer.hpp"
#include <iostream>

void customLoopFunction() {
  PrimitiveRenderer::drawLine({20, 170}, {200, 170}, sf::Color::Magenta);

  PrimitiveRenderer::drawEclipse({100, 270}, 70, 70);
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
