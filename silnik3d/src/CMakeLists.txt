
include_directories(engine engine/include)

add_subdirectory(engine)

# stb
# System has to have STB installed
# for stb_image
include_directories(/usr/include/stb REQUIRED)


add_subdirectory(test)
add_subdirectory(test2)
add_subdirectory(test3)
add_subdirectory(test4)
add_subdirectory(test5)

