#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Shape.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/Window/Event.hpp"
#include "animatedObject.hpp"
#include "log.hpp"
#include "point2d.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <functional>
#include <set>

/**
 * @brief The engine class. */
class Engine {
public:
  using Time = sf::Time;
  using Clock = sf::Clock;
  using RenderWindow = sf::RenderWindow;
  using Event = sf::Event;
  using Drawable = sf::Drawable;
  using Shape = sf::Shape;

  using eventHandler_t = std::function<void(const Event &)>;
  using drawableCollection_t = std::set<Drawable *>;
  using animatedObjecsCollection_t = std::set<AnimatedObject *>;

private:
  /** @brief Pointer to the instance.
   */
  static Engine *s_instancePtr;

  /** @brief custom function fired in the main loop.
   * */
  std::function<void()> m_loopFunction{[]() {}};

  /** @brief Window to draw stuff on.
   */
  RenderWindow m_window{};
  /** @brief Resolution of the window.
   */
  Point2d m_resoltuon{1000, 800};
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
  std::array<eventHandler_t, Event::Count> m_eventHandlers;

  /**
   *@brief Stuff that is drawn in the window each frame.
   **/
  drawableCollection_t m_drawablesCollection{};

  animatedObjecsCollection_t m_animatedObjectsCollection{};

  /**
   *@brief Clock for computing ticks. */
  Clock m_clock{};

  /**
   *@brief Duration of the last frame.
   **/
  Time m_lastFrameDuration{};

public:
  /**
   * @brief Constructor.
   **/
  Engine();
  /**
   * @brief Destructor.
   */
  ~Engine();

  /** @brief Instance getter.
   */
  static Engine &getInstance();

  /** @brief Set Max FPS.
   * @param fps max FPS.
   */
  Engine &setMaxFps(int fps);

  /** @brief Set window title.
   *  @param title Title.
   *  */
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
   * @brief Set custom event handler.
   * @param eventType Type of event that handler receives.
   * @param handler Function handling the event.
   **/
  Engine &setEventHandler(Event::EventType eventType, eventHandler_t handler);

  /** @brief Resolution getter.
   */
  Point2d getResolution() const;

  /** @brief Builds the window.
   */
  Engine &buildWindow();

  /**
   *@brief Handles events.
   */
  void handleEvents();

  /**
   * @brief Clears window to a single color.
   */
  void clear();

  /**
   * @brief Renders objects.
   */
  void render();

  /**
   * @brief Displays rendered objects.
   */
  void display();

  /**
   * @brief The main loop.
   */
  void loop();

  /**
   * @brief Window getter.
   */
  RenderWindow &getWindow();

  /**
   * @brief Adds drawable to  Collection.
   * @param drawable Drawable shape.
   */
  void add(Drawable *drawable);
  /**
   * @brief Adds animated object to Collection.
   * @param animatedObject animated object.
   */
  void add(AnimatedObject *animatedObject);

  void remove(Drawable *);

  /**
   * @brief Last frame duration getter.
   */
  Time getLastFrameDuration() const;

private:
  /**
   * @brief Draws objects.
   */
  void drawDrawables();
  /**
   * @brief Draws animated objects.
   */
  void animateObjects();
};

#endif // ENGINE_HPP_
