#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/VideoMode.hpp"
#include "SFML/Window/Window.hpp"
#include "SFML/Window/WindowStyle.hpp"
#include "drawable.hpp"
#include "point2d.hpp"
#include "primitiveRenderer.hpp"
#include <list>

class Engine {
public:
  friend PrimitiveRenderer;

private:
  /** @brief Pointer to the instance.
   */
  static Engine *s_instancePtr;

  /** @brief Window to draw stuff on.
   */
  sf::RenderWindow m_window{};
  /** @brief Resolution of the window.
   */
  Point2d m_resoltuon{800, 800};
  /** @brief Window title.
   */
  std::string m_windowTitle{"dev"};
  /**
   *@brief max fps
   **/
  int m_maxFPS{60};

  /** @brief Renderable objects collection, it will be rendered.
   */
  std::list<Drawable *> m_renderables;

  static std::ostream &s_logStream;

public:
  Engine();
  ~Engine();

  /** @brief Instance getter.
   */
  static Engine &getInstance();

  /** @brief Set Max FPS.
   */
  Engine &setMaxFps(int fps);

  /** @brief Set window title.
   *  @param title Title. */
  Engine &setWindowTitle(std::string_view title);

  /** @brief Set resolution.
   */
  Engine &setResolution(Point2d resolution);

  /** @brief Set resolution.
   */
  Engine &setResolution(Point2d::cordinate_t x, Point2d::cordinate_t y) {
    setResolution({x, y});
    return *this;
  };

  /** @brief Get resolution.
   */
  Point2d getResolution() const;

  /** @brief Build the window.
   */
  Engine &buildWindow();

  void handleEvents();
  void clear();
  void render();
  void loop();
};

#endif // ENGINE_HPP_
