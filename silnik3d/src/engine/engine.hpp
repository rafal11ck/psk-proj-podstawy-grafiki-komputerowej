#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include "SFML/System/Clock.hpp"
#include "SFML/Window.hpp"
#include "SFML/Window/ContextSettings.hpp"
#include "SFML/Window/Window.hpp"
#include "camera.hpp"
#include "drawable.hpp"
#include "shader.hpp"
#include <functional>
#include <set>

/**
 *@class
 *@brief Singleton
 **/
class Engine {

public:
  using Time = sf::Time;
  using Event = sf::Event;
  using eventHandler_t = std::function<void(const Event &)>;

  /**
   *@brief Distance to near clipping plane from camera.*/
  static constexpr float clippingPlaneNear{0.1};

  /**
   *@brief Distance to far clipping plane from camera.*/
  static constexpr float clippingPlaneFar{100};

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
  sf::Window &getWindow();

  Engine &setMaxFps(int fps);

  /**
   *@brief Add drawable to be drawn by engine.
   *
   *Added dawables will be rendered.
   *
   *@note Added object has to outlive Engine object in which case it will be
   *desroyed by ~Engine() or be removed via removeDrawable().
   *
   *@see removeDrawable()
   **/
  void addDrawable(Drawable *drawable);

  /**
   *@brief Add drawable to be drawn by engine.
   *
   *Removes drawable from engine collection.
   *
   *@warn This does not delete object.
   *
   *@see addDrawable
   **/
  void removeDrawable(Drawable *const drawable);

  Camera &getCamera();
  float getAspectRatio() const;

  /**
   *@brief Compute projection matix.
   *
   *It is based on m_camera zoom and m_window aspect ratio.
   *
   *@warn It only computes is.
   **/
  glm::mat4 computeProjectionMatrix() const;

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

  /**
   *@brief Shader for drawing objects.
   *
   **/
  Shader *m_defaultShader{nullptr};

  /**
   *@brief Collection of drawables drawn by engine.
   **/
  std::set<Drawable *> m_drawables{};

  Camera m_camera{};

private:
  Engine();
  ~Engine();

  void handleEvents();

  void render();

  /** @brief Builds the window with openGl context
   */
  Engine &buildWindow(sf::ContextSettings settings = sf::ContextSettings{
                          24, 8, 4, 3, 3, sf::ContextSettings::Core});
};

#endif // ENGINE_HPP_
