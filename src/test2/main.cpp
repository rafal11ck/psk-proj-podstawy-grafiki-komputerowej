#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "engine.hpp"
#include "log.hpp"
#include "player.hpp"
#include <iostream>
#include <utility>

Player player;

void handlePlayerMovement() {

  std::array keyBinds{
      std::pair{sf::Keyboard::Key::W, Player::MoveDirection::north},
      std::pair{sf::Keyboard::Key::S, Player::MoveDirection::south},
      std::pair{sf::Keyboard::Key::A, Player::MoveDirection::west},
      std::pair{sf::Keyboard::Key::D, Player::MoveDirection::east}};

  bool doUpdate{};
  for (auto bind : keyBinds) {
    if (sf::Keyboard::isKeyPressed(bind.first)) {
      player.setIsMoving(bind.second);
      doUpdate = true;
    }
  }

  if (doUpdate) {
    player.update();
  }
}

void keyPressedEventHandler(const sf::Event &ev) {}

void customLoop() {
  Engine &eng = Engine::getInstance();
  handlePlayerMovement();
}

int main() {
  Engine &eng =
      Engine::getInstance().setWindowTitle("dev").setMaxFps(75).buildWindow();

  eng.setEventHandler(sf::Event::KeyPressed, keyPressedEventHandler);

  sf::Texture texture{};
  texture.loadFromFile("../src/"
                       "test2/resurce/player/spritesheet.png",
                       sf::IntRect(0, 0, 300, 300));
  player.setTexture(texture);
  player.setColor(sf::Color::Blue);
  player.setMovementSpeed(150);

  eng.add(&player);

  eng.setLoopFunction(customLoop);

  eng.loop();
}
