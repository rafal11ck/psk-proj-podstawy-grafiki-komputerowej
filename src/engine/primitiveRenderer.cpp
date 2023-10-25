#include "primitiveRenderer.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Vertex.hpp"
#include "SFML/System/Vector2.hpp"
#include "engine.hpp"
#include "point2d.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <valarray>

sf::Color PrimitiveRenderer::s_defaultColor{sf::Color::Red};

sf::Color PrimitiveRenderer::getPixelColor(Point2d cord) {
  auto res{Engine::getInstance().getResolution()};
  sf::Texture texture;
  texture.create(res.getX(), res.getY());
  texture.update(Engine::getInstance().m_window);
  auto image = texture.copyToImage();
  return image.getPixel(cord.getX(), cord.getY());
}

void PrimitiveRenderer::drawPoint(const Point2d cord, sf::Color color) {
  sf::Image image;
  const auto dimestions{Engine::getInstance().m_window.getSize()};

  image.create(1, 1, color);

  sf::Texture texture;
  texture.loadFromImage(image);

  sf::Sprite sprite(texture);
  sprite.setPosition(cord.getX(), cord.getY());

  Engine::getInstance().m_window.draw(sprite);
}

void PrimitiveRenderer::drawLineIterative(Point2d a, Point2d b,
                                          sf::Color color) {
  if (a.getX() > b.getX())
    a.swap(b);
  auto dy{a.getY() - b.getY()};
  auto dx{a.getX() - b.getX()};
  auto m{static_cast<double>(dy) / dx};

  if (std::abs(m) < 1) {

    double y{static_cast<double>(a.getY())};
    for (auto x{a.getX()}; x <= b.getX(); ++x) {
      drawPoint({x, static_cast<Point2d::cordinate_t>(y + 0.5)}, color);
      y += m;
    }
  } else {
    if (a.getY() > b.getY())
      a.swap(b);
    auto m{static_cast<double>(dx) / dy};
    double x{static_cast<double>(a.getX())};
    for (auto y{a.getY()}; y <= b.getY(); ++y) {
      drawPoint({static_cast<Point2d::cordinate_t>(x + 0.5), y}, color);
      x += m;
    }
  }
}

void PrimitiveRenderer::drawLine(Point2d a, Point2d b, sf::Color color) {
  sf::Vertex line[] = {sf::Vertex(sf::Vector2f(a.getX(), a.getY()), color),
                       sf::Vertex(sf::Vector2f(b.getX(), b.getY()), color)};

  Engine::getInstance().m_window.draw(line, 2, sf::Lines);
}

void PrimitiveRenderer::drawLine(const std::vector<Point2d> &points,
                                 sf::Color color, bool lastToFirst) {
  for (int i{}; i < points.size() - 1; ++i) {
    drawLine(points[i], points[i + 1]);
  }
  if (lastToFirst)
    drawLine(points[0], points.back());
}

void PrimitiveRenderer::drawCircle(Point2d origin, int r) {
  double step = 1.0 / r;
  for (double i{}; i < M_PI / 4; i += step) {
    Point2d cord{Point2d{static_cast<Point2d::cordinate_t>(r * cos(i)),
                         static_cast<Point2d::cordinate_t>(r * sin(i))}};

    drawPoint(origin + Point2d{cord.getX(), cord.getY()});
    drawPoint(origin + Point2d{cord.getX(), -cord.getY()});
    drawPoint(origin + Point2d{-cord.getX(), cord.getY()});
    drawPoint(origin + Point2d{-cord.getX(), -cord.getY()});
    drawPoint(origin + Point2d{cord.getY(), cord.getX()});
    drawPoint(origin + Point2d{cord.getY(), -cord.getX()});
    drawPoint(origin + Point2d{-cord.getY(), cord.getX()});
    drawPoint(origin + Point2d{-cord.getY(), -cord.getX()});
  }
}

void PrimitiveRenderer::drawEclipse(Point2d origin, int rx, int ry) {
  double step = 1.0 / rx;
  for (double i{}; i < M_PI / 2; i += step) {
    Point2d cord{Point2d{static_cast<Point2d::cordinate_t>(rx * cos(i)),
                         static_cast<Point2d::cordinate_t>(ry * sin(i))}};

    drawPoint(origin + Point2d{cord.getX(), cord.getY()});
    drawPoint(origin + Point2d{cord.getX(), -cord.getY()});
    drawPoint(origin + Point2d{-cord.getX(), cord.getY()});
    drawPoint(origin + Point2d{-cord.getX(), -cord.getY()});
  }
}

void PrimitiveRenderer::fill(Point2d origin, sf::Color paintColor,
                             sf::Color boundaryColor) {
  if (getPixelColor(origin) == paintColor ||
      getPixelColor(origin) == boundaryColor)
    return;

  drawPoint(origin, paintColor);
  fill(origin + Point2d{1, 0}, paintColor, boundaryColor);
  fill(origin + Point2d{0, -1}, paintColor, boundaryColor);
  fill(origin + Point2d{-1, 0}, paintColor, boundaryColor);
  fill(origin + Point2d{0, 1}, paintColor, boundaryColor);
}
