#include "engine.hpp"

Engine Engine::s_singletonInstance{Engine()};

Engine &Engine::getEngine() { return s_singletonInstance; }

Engine::Engine() { initGraphicLib(); }

void Engine::initGraphicLib() { m_outStream << "Initialzing graphic lib\n"; }
