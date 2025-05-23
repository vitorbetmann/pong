cmake_minimum_required(VERSION 3.16)
project(pong LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SOURCES "src/*.c")

add_executable(pong ${SOURCES})

if(APPLE)
    find_package(raylib REQUIRED)
    target_link_libraries(pong PRIVATE raylib)

elseif(WIN32)
    set(RAYLIB_ROOT "C:/libs/raylib")

    target_include_directories(pong PRIVATE "${RAYLIB_ROOT}/include")

    target_link_libraries(pong PRIVATE
        "${RAYLIB_ROOT}/lib/libraylib.a"
        winmm
        gdi32
        opengl32
        kernel32
        user32
        shell32
        ole32
        oleaut32
        uuid
        comdlg32
        advapi32
    )
endif()