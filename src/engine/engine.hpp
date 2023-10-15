#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <iostream>

/**
 *@brief Engine.
 *
 *Singleton class.
 * */
class Engine {
  /**
   * @brief member instance. */
  static Engine s_singletonInstance;

public:
  /**
   *@brief Stream used for output. */
  std::ostream &m_outStream{std::cerr};

  /**
   * @brief Engine getter. */
  static Engine &getEngine();

  /**
   * @brief main loop */
  void loop();

private:
  /**
   *@brief Engine constructor. */
  Engine();

  /**
   * @brief Initialize. */
  void initGraphicLib();
};

#endif // ENGINE_HPP_
