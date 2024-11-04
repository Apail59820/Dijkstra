cmake_minimum_required(VERSION 3.11)
project(Dijkstra)

set(CMAKE_CXX_STANDARD 20)

set(SFML_VERSION 2.6.1)
set(IMGUI_VERSION 1.89.9)

include(FetchContent)

cmake_policy(SET CMP0153 NEW)

set(SFML_DIR "/opt/homebrew/opt/sfml/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES TRUE)


find_package(SFML ${SFML_VERSION} REQUIRED COMPONENTS graphics window system)

FetchContent_Declare(
        imgui
        GIT_REPOSITORY "https://github.com/ocornut/imgui.git"
        GIT_TAG "v${IMGUI_VERSION}"
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_Declare(
        imgui-sfml
        GIT_REPOSITORY "https://github.com/SFML/imgui-sfml.git"
        GIT_TAG "v2.6"
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(IMGUI_DIR imgui)

FetchContent_MakeAvailable(imgui)
FetchContent_MakeAvailable(imgui-sfml)

add_executable(Dijkstra main.cpp
        Include/Point.h
        Source/Point.cpp
        Include/FontManager.h
        Source/FontManager.cpp
)

target_link_libraries(Dijkstra
        PUBLIC
        sfml-system
        sfml-window
        sfml-graphics
        ImGui-SFML::ImGui-SFML
)

