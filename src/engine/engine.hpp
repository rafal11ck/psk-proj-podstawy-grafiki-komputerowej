#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

/**
 *@brief Engine.
 *
 *Singleton class.
 * */
class Engine {
  using mainWindow_t = sf::RenderWindow;

public:
  /**
   * @brief Engine getter. */
  static Engine &getEngine();

  /**
   * @brief Sets max framerate of m_mainWindow */
  void setMaxFrameRate(int fps);

  /**
   * @brief main loop */
  void loop();

private:
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

  /**
   *@brief Engine constructor. */
  Engine(sf::VideoMode mode = {1920u, 1080u}, std::string title = "dev");

  /**
   * @brief Initialize main window */
  void init(sf::VideoMode mode, std::string title);
};

#endif // ENGINE_HPP_
