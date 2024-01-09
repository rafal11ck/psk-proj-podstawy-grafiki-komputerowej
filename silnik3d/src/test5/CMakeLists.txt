include_directories(${CMAKE_BINARY_DIR}/generated/)
add_executable(test5 main.cpp)
target_link_libraries(test5 engine)
