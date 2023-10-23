#include "SFML/Graphics/Color.hpp"
#include "engine.hpp"
#include "primitiveRenderer.hpp"

void customLoopFunction() {
  PrimitiveRenderer::drawLine({20, 170}, {200, 170}, sf::Color::Magenta);

  PrimitiveRenderer::drawEclipse({100, 270}, 70, 70);
}

int main() {
  Engine &eng = Engine::getInstance()
                    .setWindowTitle("dev")
                    .setMaxFps(1)
                    .setLoopFunction(customLoopFunction)
                    .buildWindow();

  eng.loop();
}
