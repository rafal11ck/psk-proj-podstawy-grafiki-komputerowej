#include "engine.hpp"
#include <iostream>

int main() {
  Engine &eng = Engine::getInstance().setWindowTitle("dev").buildWindow();

  eng.setEventHandler(
      Engine::Event::MouseButtonPressed, [](const Engine::Event &ev) {
        std::cout << "Custom event handler Mouse button press "
                  << ev.mouseButton.button << '\t' << ev.mouseButton.x << '\t'
                  << ev.mouseButton.y << "\n";
      });

  eng.loop();
}
