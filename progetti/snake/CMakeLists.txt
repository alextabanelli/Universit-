cmake_minimum_required(VERSION 3.30)
project(snake)

set(CMAKE_CXX_STANDARD 20)

include_directories(C:/MinGW/include/ncurses)
link_directories(C:/MinGW/lib)

add_executable(snake main.cpp
        snake.cpp
        snake.h
        board.cpp
        board.h
        menu.cpp
        menu.cpp
        menu.h
        levelmanager.cpp
        levelmanager.h)
target_link_libraries(snake ncurses)