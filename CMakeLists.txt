cmake_minimum_required(VERSION 3.16)
project(pong C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

file(GLOB SOURCES "src/*.c")

add_executable(pong ${SOURCES})

if (APPLE)
    find_package(raylib REQUIRED)
    target_link_libraries(pong raylib)
elseif(WIN32)
    include_directories("C:/libs/raylib/include")
    target_link_libraries(pong
    "C:/libs/raylib/lib/libraylib.a"
    winmm
    gdi32
    opengl32)
endif()