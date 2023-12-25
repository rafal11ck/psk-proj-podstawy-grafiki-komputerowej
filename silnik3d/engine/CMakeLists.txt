
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

include(FetchContent)

# sfml
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

if(WIN32)
    add_custom_command(
        TARGET CMakeSFMLProject
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:CMakeSFMLProject>
        VERBATIM)
endif()


# glew
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})

# glm
find_package(glm REQUIRED)

# stb
include_directories(/usr/include/stb REQUIRED)

# file(COPY resources DESTINATION resources)

include_directories(include)
include_directories(${GLM_INCLUDE_DIRS})

add_executable(engine engine.cpp include/shader.hpp shader.cpp stb/stb_image.h stb_image.cpp)
target_link_libraries(engine ${OPENGL_gl_LIBRARY})
target_link_libraries(engine glm)
target_link_libraries(engine ${GLEW_LIBRARIES})
target_link_libraries(engine sfml-graphics)
