#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "animatedObject.hpp"
#include "animatedSpriteSheet.hpp"
#include "ball.hpp"
#include "bush.hpp"
#include "engine.hpp"
#include "fidgetSpinner.hpp"
#include "gamePlayer.hpp"
#include "log.hpp"
#include "point2d.hpp"
#include <iostream>
#include <list>
#include <utility>

using sf::IntRect;

GamePlayer player{};
std::array<Bush, 4> bush{};
Engine &eng = Engine::getInstance();
FidgetSpinner fidgetSpinner{"resource/fidgetSpinner"};
std::list<Ball *> balls;

Ball *ball = new Ball(30);

void throwBall(Point2d pos, Point2d vector) {
  Ball *bal = new Ball();
  bal->setPositon(pos);
  bal->setMoveVectorBase(vector);
  balls.push_back({new Ball()});
  eng.add(ball);
}

void initialziePlayer() {
  LOGINFON;
  player.setMovementSpeed(50);
  player.setColor(sf::Color::Yellow);
  eng.add(&player);
}

void initializeBush() {
  for (ssize_t i{}; i < bush.max_size(); ++i) {
    LOGINFO << i << '\n';
    eng.add(&(bush[i]));
  }
  bush[0].setPosition({300, 150});
  bush[1].setPosition({700, 550});
  bush[2].setPosition({100, 450});
  bush[3].setPosition({800, 250});
}

void handlePlayerMovement() { player.update(); }

void handleBalls() {
  for (auto it{balls.begin()}; it != balls.end(); ++it) {
    Ball *b = *it;
    b->update();
    if (b->wasRemovedFromEngine()) {
      delete b;
      balls.erase(it);
    }
  }
}

void customLoop() { handlePlayerMovement(); }

void spinTheFidget() {

  Point2d pla{Point2d(player.sf::Sprite::getPosition()) +
              Point2d{player.sf::Sprite::getTextureRect().getSize()} * 0.5};
  Point2d fig{Point2d{fidgetSpinner.sf::Sprite::getPosition()} +
              Point2d{fidgetSpinner.getTextureRect().getSize()} * 0.5};

  float dist(pla.distanceTo(fig));

  LOGINFO << dist << '\n';
  if (dist < 300) {
    fidgetSpinner.addRotationSpeed(8);
  }
}

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
  case sf::Keyboard::Space:
    spinTheFidget();
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

void initializeFidgetSpinner() {
  fidgetSpinner.setPosition({600, 600});
  eng.add(&fidgetSpinner);
}

int main() {
  LOGTRACEN;
  eng.setWindowTitle("dev").setMaxFps(75).buildWindow();
  eng.setEventHandler(sf::Event::KeyPressed, keyPressedEventHandler);
  eng.setEventHandler(sf::Event::KeyReleased, keyReleasedEventHandler);
  eng.setLoopFunction(customLoop);

  initialziePlayer();
  initializeBush();
  initializeFidgetSpinner();

  eng.loop();
}
