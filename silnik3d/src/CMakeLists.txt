add_executable(engine engine.cpp)

target_link_libraries(engine sfml-graphics)
target_link_libraries(engine ${OPENGL_gl_LIBRARY})

find_package(GLEW REQUIRED)
target_link_libraries(engine ${GLEW_LIBRARIES})

target_compile_features(engine PRIVATE cxx_std_20)
