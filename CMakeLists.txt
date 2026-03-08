cmake_minimum_required(VERSION 3.29)
project(hexxagon)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS FALSE)

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY  https://github.com/SFML/SFML
        GIT_TAG         2.6.1
)

FetchContent_MakeAvailable(SFML)

add_executable(hexxagon main.cpp
        Cpp/Board.cpp
        Cpp/Board.h
        Cpp/Menu.cpp
        Cpp/Menu.h
        Cpp/Hexagon.cpp
        Cpp/Hexagon.h
        Cpp/Scores.cpp
        Cpp/Scores.h)
target_link_libraries(hexxagon sfml-graphics)