#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "animatedObject.hpp"
#include "bush.hpp"
#include "engine.hpp"
#include "gamePlayer.hpp"
#include "log.hpp"
#include <iostream>
#include <utility>

using sf::IntRect;

GamePlayer player{};
std::array<Bush, 4> bush{};
Engine &eng = Engine::getInstance();

void initialziePlayer() {
  LOGINFON;
  player.setMovementSpeed(150);
  player.setColor(sf::Color::Red);

  eng.add(&player);
}

void initializeBush() {
  for (ssize_t i{}; i < bush.max_size(); ++i) {
    LOGINFO << i << '\n';
    bush[i].setPosition({300, 150 * (i + 1.f)});
    eng.add(&(bush[i]));
  }
}

void handlePlayerMovement() { player.update(); }

void customLoop() { handlePlayerMovement(); }

std::array keyBinds{
    std::pair{sf::Keyboard::Key::W, Player::MoveDirection::north},
    std::pair{sf::Keyboard::Key::S, Player::MoveDirection::south},
    std::pair{sf::Keyboard::Key::A, Player::MoveDirection::west},
    std::pair{sf::Keyboard::Key::D, Player::MoveDirection::east}};

void keyPressedEventHandler(const sf::Event &ev) {
  switch (ev.key.code) {
  case sf::Keyboard::W:
    player.setIsMoving(Player::MoveDirection::north);
    break;
  case sf::Keyboard::A:
    player.setIsMoving(Player::MoveDirection::west);
    break;
  case sf::Keyboard::S:
    player.setIsMoving(Player::MoveDirection::south);
    break;
  case sf::Keyboard::D:
    player.setIsMoving(Player::MoveDirection::east);
    break;
  case sf::Keyboard::Escape:
    eng.getWindow().close();
    break;

  default:
    break;
  }
}

void keyReleasedEventHandler(const sf::Event &ev) {
  switch (ev.key.code) {
  case sf::Keyboard::W:
    player.stopMoving(Player::MoveDirection::north);
    break;
  case sf::Keyboard::A:
    player.stopMoving(Player::MoveDirection::west);
    break;
  case sf::Keyboard::S:
    player.stopMoving(Player::MoveDirection::south);
    break;
  case sf::Keyboard::D:
    player.stopMoving(Player::MoveDirection::east);
    break;
  default:
    break;
  }
}

int main() {
  LOGTRACEN;
  eng.setWindowTitle("dev").setMaxFps(75).buildWindow();
  eng.setEventHandler(sf::Event::KeyPressed, keyPressedEventHandler);
  eng.setEventHandler(sf::Event::KeyReleased, keyReleasedEventHandler);
  eng.setLoopFunction(customLoop);

  initialziePlayer();
  initializeBush();

  eng.loop();
}
