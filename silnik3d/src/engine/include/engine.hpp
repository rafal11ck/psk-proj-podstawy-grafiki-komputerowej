#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include "SFML/System/Clock.hpp"
#include "SFML/Window.hpp"
#include "SFML/Window/ContextSettings.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Window.hpp"
#include "camera.hpp"
#include "drawable.hpp"
#include "light.hpp"
#include "resources.hpp"
#include "shader.hpp"
#include <functional>
#include <set>
#include <string_view>

/**
 *@brief Singleton Engine class
 **/
class Engine {

public:
  using Time = sf::Time;
  using Event = sf::Event;
  using eventHandler_t = std::function<void(const Event &)>;

  enum class ProjectionType { orthogonal, perspective, max_ProjectionType };

  /**
   *@brief Distance to near clipping plane from camera.*/
  static constexpr float s_clippingPlaneNear{0.1};

  /**
   *@brief Distance to far clipping plane from camera.*/
  static constexpr float s_clippingPlaneFar{100};

  static const std::string s_defaultShaderDir;

  static const std::string s_defaultShaderPathVertex;
  static const std::string s_defaultShaderPathFragment;

  static const unsigned int s_maxlightcount;

  /// @brief Engine instance getter 
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
   *@warning This does not delete object.
   *
   *@see addDrawable
   **/
  void removeDrawable(Drawable *const drawable);

  void addLight(Light *const light);

  void removeLight(Light *const light);

  Camera &getCamera();
  float getAspectRatio() const;

  /**
   *@brief Compute projection matix.
   *
   *It is based on m_camera zoom and m_window aspect ratio.
   *
   *@warning It only computes is.
   **/
  glm::mat4 computeProjectionMatrix() const;

  /**
   *@brief Set if engine should change camera angles on mouse move within it's
   *widnow.
   **/
  void setCameraHandlingMouse(bool enbaled);

  /**
   *@brief Set if engine should change camera positon on mouse move within
   *it's widnow.
   **/
  void setCameraHandlingKeyboard(bool enbaled);

  void setProjectionType(ProjectionType projectionType);

  void moveMouseToCenterOfWindow();

  void setWireframeMode(bool enabled);

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

  /**
   *@brief Collection of lights.
   **/
  std::set<Light *> m_lights{};

  Camera m_camera{};

  /**
   *@brief Does engine change camrea angle o mouse move
   **/
  bool m_engineHandleCameraOnMouseMove{false};

  /**
   *@brief Does engine change camrea position o mouse move.
   **/
  bool m_cameraHandlingKeyboard{false};

  ProjectionType m_projectionType{ProjectionType::orthogonal};

private:
  Engine();
  ~Engine();

  void handleEvents();

  void render();

  /** @brief Builds the window with openGl context
   */
  Engine &buildWindow(sf::ContextSettings settings = sf::ContextSettings{
                          24, 8, 4, 3, 3, sf::ContextSettings::Core});
  /**
   *@brief Builtin camera handler.
   *
   *Handles mouse movement event.
   *
   **/
  void handleCameraMouseMove(const sf::Event ev);

  /**
   *@brief Builtin camera handler.
   *
   *Used in main loop.
   **/
  void handleCameraKeyboard();

  void updateShaderLights(Shader &shader) const;
};

#endif // ENGINE_HPP_
