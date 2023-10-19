#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include "drawable.hpp"
#include "point2d.hpp"
#include "primitiveRenderer.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <iostream>
#include <list>
#include <map>
#include <vector>

/**
 *@brief Engine.
 *
 *Singleton class.
 * */
class Engine {
  friend PrimitiveRenderer;

private:
  /**
   *@brief Collection of objects that will be drawn */
  std::list<Drawable *> m_rendererDrawables;

  using mainWindow_t = sf::RenderWindow;

public:
  /**
   * @brief Engine getter. */
  static Engine &getEngine();

  /**
   * @brief Get out stream */
  std::ostream &getOutStream();

  Point2d getWindowDimensions() const;

  /**
   * @brief Sets max framerate of m_mainWindow */
  void setMaxFrameRate(int fps);

  /**
   * @brief Render stuff
   */
  void render();

  /**
   * @brief main loop */
  void loop();

private:
  ~Engine();

  /**
   * @brief member instance. */
  static Engine s_singletonInstance;

  /**
   *@brief Stream used for output. */
  std::ostream &m_outStream{std::cerr};

  /**
   * @brief
   * Window.
   *  */
  mainWindow_t m_mainWindow;

  /** @brief Gaps between ticks. */
  sf::Time m_tickTimeStep{sf::seconds(1.0f / 30.0f)};

  /**
   *@brief Engine constructor. */
  Engine(sf::VideoMode mode = {1920u, 1080u}, std::string title = "dev");

  /**
   * @brief Initialize main window */
  void init(sf::VideoMode mode, std::string title);

  /**
   *@brief Add drawable
   *@param drawable Drawable that will be added.
   *@return Iterator.
   *
   *@note Iterator can be used to remove drawable added.
   **/
  const std::list<Drawable *>::iterator addDrawable(Drawable *drawable) {
    m_rendererDrawables.push_back(drawable);
    auto it{m_rendererDrawables.end()};
    --it;

    return it;
  }

  /**
   *@brief Remove drawable
   *@param it Iterator to drawable to be removed
   *
   **/
  void removeDrawable(const std::list<Drawable *>::iterator it) {
    m_rendererDrawables.erase(it);
  }
};

#endif // ENGINE_HPP_
