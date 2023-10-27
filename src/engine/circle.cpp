
#include "circle.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "engine.hpp"

void Circle::draw() const { Engine::getInstance().getWindow().draw(m_shape); }
