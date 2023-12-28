#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include "SFML/System/Clock.hpp"
#include "SFML/Window.hpp"
#include "SFML/Window/ContextSettings.hpp"
#include "SFML/Window/Window.hpp"
#include "log.hpp"
#include <functional>

/**
 *@class
 *@brief Singleton
 **/
class Engine {

public:
  using Time = sf::Time;
  using Event = sf::Event;
  using eventHandler_t = std::function<void(const Event &)>;

  static Engine &getInstance();

  Time getLastFrameDuration() const;

  /** @brief Set function that is invoked in the main loop.
   *  @param function Function that will be called in loop.
   * */
  Engine &setLoopFunction(std::function<void()> function) {
    m_loopFunction = function;
    return *this;
  };

  /**
   * @brief Set custom event handler.
   * @param eventType Type of event that handler receives.
   * @param handler Function handling the event.
   **/
  Engine &setEventHandler(Event::EventType eventType, eventHandler_t handler);

  /**
   * @brief The main loop.
   */
  void loop();

  const sf::Window &getWindow() const;

  Engine &setMaxFps(int fps);

private:
  static Engine *s_instance;

  bool isLoopRunning{false};

  sf::Time m_lastFrameDuration{};
  sf::Clock m_clockFrame{};

  sf::Window m_window{};

  /** @brief custom function fired in the main loop.
   * */
  std::function<void()> m_loopFunction{[]() {}};

  /**
   *@brief Custom functions handling events.
   **/
  std::array<eventHandler_t, Event::Count> m_eventHandlers;

private:
  Engine();

  void handleEvents();

  /** @brief Builds the window with openGl context
   */
  Engine &buildWindow(sf::ContextSettings settings = sf::ContextSettings{
                          24, 8, 4, 3, 3, sf::ContextSettings::Core});
};

#endif // ENGINE_HPP_
