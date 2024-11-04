cmake_minimum_required(VERSION 3.29)
project(Dijkstra)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_MODULE_PATH "/opt/homebrew/Cellar/sfml/2.6.1/share/SFML/cmake")
find_package(SFML 2.6 COMPONENTS system window graphics REQUIRED)

add_executable(Dijkstra main.cpp)
target_link_libraries(Dijkstra sfml-system sfml-window sfml-graphics)
