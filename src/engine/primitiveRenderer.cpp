#include "primitiveRenderer.hpp"
#include "SFML/Graphics/Color.hpp"
#include "engine.hpp"
#include "point2d.hpp"
#include <SFML/Graphics.hpp>
#include <valarray>

void PrimitiveRenderer::drawPoint(const Point2d cord, sf::Color color) {

  sf::Image image;
  const auto dimestions{Engine::getEngine().getWindowDimensions()};

  image.create(1, 1, color);

  sf::Texture texture;
  texture.loadFromImage(image);

  sf::Sprite sprite(texture);
  sprite.setPosition(cord.getX(), cord.getY());

  Engine::getEngine().m_mainWindow.draw(sprite);
}

void PrimitiveRenderer::drawLineIterative(Point2d a, Point2d b) {
  if (a.getX() > b.getX())
    a.swap(b);
  auto dy{a.getY() - b.getY()};
  auto dx{a.getX() - b.getX()};
  auto m{static_cast<double>(dy) / dx};

  if (std::abs(m) < 1) {

    double y{static_cast<double>(a.getY())};
    for (auto x{a.getX()}; x <= b.getX(); ++x) {
      drawPoint({x, static_cast<Point2d::cordinate_t>(y + 0.5)});
      y += m;
    }
  } else {
    if (a.getY() > b.getY())
      a.swap(b);
    auto m{static_cast<double>(dx) / dy};
    double x{static_cast<double>(a.getX())};
    for (auto y{a.getY()}; y <= b.getY(); ++y) {
      drawPoint({static_cast<Point2d::cordinate_t>(x + 0.5), y},
                sf::Color::Cyan);
      x += m;
    }
  }
}
