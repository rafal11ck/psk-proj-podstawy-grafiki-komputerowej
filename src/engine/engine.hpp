#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/Window/Event.hpp"
#include "drawable.hpp"
#include "point2d.hpp"
#include "primitiveRenderer.hpp"
#include <functional>
#include <set>

/**
 * @brief The god. */
class Engine {
public:
  // friend PrimitiveRenderer;

  using eventHandler_t = std::function<void(const sf::Event &)>;
  using drawableCollection_t = std::set<const Drawable *>;
  using Time = sf::Time;
  using Clock = sf::Clock;
  using RenderWindow = sf::RenderWindow;

private:
  /** @brief Pointer to the instance.
   */
  static std::ostream &s_logStream;
  static Engine *s_instancePtr;

  /** @brief custom function fired in the main loop.
   * */
  std::function<void()> m_loopFunction{[]() {}};

  /** @brief Window to draw stuff on.
   */
  RenderWindow m_window{};
  /** @brief Resolution of the window.
   */
  Point2d m_resoltuon{800, 800};
  /** @brief Window title.
   */
  std::string m_windowTitle{"dev"};
  /**
   *@brief Max FPS.
   **/
  int m_maxFPS{60};

  /**
   *@brief Custom functions handling events.
   **/
  std::array<eventHandler_t, sf::Event::Count> m_eventHandlers;

  /**
   *@brief Stuff that is drawn in window each frame
   **/
  drawableCollection_t m_drawablesCollection{};

  /**
   *@brief Clock for computing ticks. */
  Clock m_clock{};

  /**
   *@brief Duration of last frame.
   **/
  Time m_lastFrameDuration{};

public:
  /**
   * @brief Constructor
   *
   **/
  Engine();
  ~Engine();

  /** @brief Instance getter.
   */
  static Engine &getInstance();

  /** @brief Set Max FPS.
   * @param fps max FPS.
   */
  Engine &setMaxFps(int fps);

  /** @brief Set window title.
   *  @param title Title. */
  Engine &setWindowTitle(std::string_view title);

  /** @brief Set resolution.
   * @param resolution Resolution to be set.
   */
  Engine &setResolution(Point2d resolution);

  /** @brief Set resolution.
   */
  Engine &setResolution(Point2d::cordinate_t x, Point2d::cordinate_t y) {
    setResolution({x, y});
    return *this;
  };

  /** @brief Set function that is invoked in the main loop.
   *  @param function Function that will be called in loop.
   * */
  Engine &setLoopFunction(std::function<void()> function) {
    m_loopFunction = function;
    return *this;
  };

  /**
   * @brief Set custom event handler
   * @param eventType Type of event that handler receives.
   * @param handler Function handling the event
   **/
  Engine &setEventHandler(sf::Event::EventType eventType,
                          eventHandler_t handler);

  /** @brief Get resolution.
   */
  Point2d getResolution() const;

  /** @brief Build the window.
   */
  Engine &buildWindow();

  void handleEvents();
  void clear();
  void render();
  void display();

  void loop();

  RenderWindow &getWindow();

  void add(Drawable *drawable);

  Time getLastFrameDuration() const;
};

#endif // ENGINE_HPP_
