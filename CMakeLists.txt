cmake_minimum_required(VERSION 3.9)
project(life)

set(PROJECT_FILES main.cpp field.h logic.h app.h setup.h)

set(CMAKE_CXX_STANDARD 14)
link_libraries(nana X11 Xft pthread rt fontconfig stdc++fs)

add_executable(life ${PROJECT_FILES})