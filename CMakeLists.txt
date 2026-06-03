cmake_minimum_required(VERSION 3.20)

project(Yonder)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML REQUIRED COMPONENTS Graphics Window System)

add_executable(Yonder
    main.cpp
    yonder.cpp
    civ.cpp
    tile.cpp
    resource.cpp
    globals.cpp
)

target_link_libraries(Yonder PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)