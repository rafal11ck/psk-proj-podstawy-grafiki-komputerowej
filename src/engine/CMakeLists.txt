add_library(engine
  engine.hpp engine.cpp
  point2d.hpp point2d.cpp
  primitiveRenderer.hpp primitiveRenderer.cpp
  drawable.hpp drawable.cpp
  lineSegment.hpp lineSegment.cpp
  circle.hpp circle.cpp
)
target_link_libraries(engine sfml-graphics)
target_compile_features(engine PRIVATE cxx_std_20)
