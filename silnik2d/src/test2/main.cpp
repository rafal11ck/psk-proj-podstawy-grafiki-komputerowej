#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"
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
#include "player.hpp"
#include "point2d.hpp"
#include <cstdlib>
#include <iostream>
#include <list>
#include <random>
#include <utility>

using sf::IntRect;

GamePlayer player{};
std::array<Bush, 4> bush{};
Engine &eng = Engine::getInstance();
FidgetSpinner fidgetSpinner{"resource/fidgetSpinner"};
std::list<Ball *> balls;

Ball *throwBall(Point2d pos, Point2d vector) {
  Ball *bal = new Ball();
  bal->setPositon(pos);
  bal->setMoveVectorBase(vector);
  balls.push_back(bal);
  eng.add(bal);
  return bal;
}

sf::Color getRandomColor() {
  return {static_cast<sf::Uint8>(rand() % 256),
          static_cast<sf::Uint8>(rand() % 256),
          static_cast<sf::Uint8>(rand() % 256)};
}

void throwBallPlayer() {
  Ball *bal{throwBall(
      static_cast<Point2d>(
          player.GameObject::getPosition() +
          static_cast<Point2d>(player.sf::Sprite::getTextureRect().getSize()) *
              0.5),
      player.getMoveVectorOrigin())};

  bal->setMovementSpeed(80);
  bal->setFillColor(getRandomColor());
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

  for (auto it{balls.begin()}; it != balls.end();) {
    auto it2{it};
    ++it;
    Ball *b = *it2;
    b->update();
    if (b->isDead()) {
      Engine::getInstance().remove(b);
      balls.remove(b);
      delete b;
    }
  }
}

void customLoop() {
  handlePlayerMovement();
  handleBalls();
}

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

  case sf::Keyboard::F:
    throwBallPlayer();
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
  throwBall({100, 0}, {1, 1});

  eng.loop();
}
