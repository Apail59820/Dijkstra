# Dijsktra

This is a small project about Dijkstra's algorithm.
As I never learned it, i wanted to learn it the hard way by adding graphical
visualisation and configuration though a graphic library in C++.
- Create points by selecting "Add Point" and left click
- Create routes by selection "Create route"
  - Hold left-click on the first point and release it on the second one
- Define starting or ending point by clicking button, then right click on any point you've added.

Exit any mode by pressing right-click on a blank zone.

[](images/demo_nav.gif)
[](images/demo_path.gif)

## How to Install

1. Install Git and CMake. Use your system's package manager if available.
1. If you use Linux, install SFML's dependencies using your system package manager. On Ubuntu and other Debian-based distributions you can use the following commands:
    ```
    sudo apt update
    sudo apt install \
        libxrandr-dev \
        libxcursor-dev \
        libudev-dev \
        libfreetype-dev \
        libopenal-dev \
        libflac-dev \
        libvorbis-dev \
        libgl1-mesa-dev \
        libegl1-mesa-dev
    ```
1. Configure and build your project. Most popular IDEs support CMake projects with very little effort on your part.
    - [VS Code](https://code.visualstudio.com) via the [CMake extension](https://code.visualstudio.com/docs/cpp/cmake-linux)
    - [Visual Studio](https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-170)
    - [CLion](https://www.jetbrains.com/clion/features/cmake-support.html)
    - [Qt Creator](https://doc.qt.io/qtcreator/creator-project-cmake.html)

    Using CMake from the command line is straightforward as well.
    Be sure to run these commands in the root directory of the project you just created.

    ```
    cmake -B build
    cmake --build build
    ```
1. Enjoy!

## License

The source code is licensed under Public Domain
