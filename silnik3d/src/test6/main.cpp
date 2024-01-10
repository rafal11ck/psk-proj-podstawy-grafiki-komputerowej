#include "engine.hpp"
#include <iostream>

Engine &engine{Engine::getInstance()};

int main() { engine.loop(); }
