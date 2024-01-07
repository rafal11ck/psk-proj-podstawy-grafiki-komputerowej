
include_directories(engine engine/include)

add_subdirectory(engine)

add_subdirectory(test)
add_subdirectory(test2)
add_subdirectory(test3)
add_subdirectory(test4)
add_subdirectory(test5)

include_directories(${CMAKE_BINARY_DIR}/gnereated PUBLIC)
