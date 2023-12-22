
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

include(FetchContent)


FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG        master
)

FetchContent_MakeAvailable(glad)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG        master
)

FetchContent_MakeAvailable(glm)

FetchContent_Declare(
  stb_image
  GIT_REPOSITORY https://github.com/nothings/stb.git
  GIT_TAG master
)

add_executable(engine engine.cpp shader.hpp shader.cpp)
target_link_libraries(engine glad)
target_link_libraries(engine glm)
target_link_libraries(engine sfml-graphics)
target_link_libraries(engine ${OPENGL_gl_LIBRARY})
target_link_libraries(engine ${GLEW_LIBRARIES})
target_compile_features(engine PRIVATE cxx_std_20)
