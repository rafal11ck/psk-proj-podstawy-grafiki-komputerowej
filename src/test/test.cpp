#include "SFML/Graphics/Color.hpp"
#include "engine.hpp"
#include "primitiveRenderer.hpp"

void customLoopFunction() {
  PrimitiveRenderer::drawLine({20, 170}, {200, 170}, sf::Color::Magenta);

  PrimitiveRenderer::drawLine({0, 0},
                              {Engine::getInstance().getResolution().getX(),
                               Engine::getInstance().getResolution().getY()},
                              sf::Color::Yellow);
  PrimitiveRenderer::drawEclipse({100, 270}, 70, 70);
}

int main() {
  Engine &eng = Engine::getInstance()
                    .setWindowTitle("dev")
                    .setMaxFps(30)
                    .setLoopFunction(customLoopFunction)
                    .buildWindow();

  eng.loop();
}
