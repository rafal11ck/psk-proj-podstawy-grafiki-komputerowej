add_library(engine
circleShape.cpp
circleShape.hpp
drawable.cpp
drawable.hpp
engine.cpp
engine.hpp
lineSegment.cpp
lineSegment.hpp
point2d.cpp
point2d.hpp
primitiveRenderer.cpp
primitiveRenderer.hpp
rectangleShape.cpp
rectangleShape.hpp
)
target_link_libraries(engine sfml-graphics)
target_compile_features(engine PRIVATE cxx_std_20)
