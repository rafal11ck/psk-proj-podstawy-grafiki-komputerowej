add_library(engine
engine.cpp
engine.hpp
GameObject.cpp
GameObject.hpp
lineSegment.cpp
lineSegment.hpp
log.cpp
log.hpp
player.cpp
player.hpp
point2d.cpp
point2d.hpp
updateableObject.cpp
updateableObject.hpp
)
target_link_libraries(engine sfml-graphics)
target_compile_features(engine PRIVATE cxx_std_20)
