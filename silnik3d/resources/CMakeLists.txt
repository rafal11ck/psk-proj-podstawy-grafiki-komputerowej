configure_file(resources.hpp.in ${CMAKE_BINARY_DIR}/generated/resources.cpp)
include_directories(${CMAKE_BINARY_DIR}/generated/)
message(${CMAKE_BINARY_DIR}/generated/)
