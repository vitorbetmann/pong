cmake_minimum_required(VERSION 3.16)
project(pong C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

file(GLOB SRC_FILES CONFIGURE_DEPENDS src/*.c)
add_executable(pong ${SRC_FILES})
find_package(raylib REQUIRED)
target_link_libraries(pong raylib)
