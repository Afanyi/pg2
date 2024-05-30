cmake_minimum_required(VERSION 3.5)

project(praktikum_2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(praktikum_2 main.cpp
    Tile.cpp
    Tile.h
    Character.cpp
    Character.h
    Level.h
    Level.cpp
    DungeonCrawler.cpp
    DungeonCrawler.h
    AbstractUI.cpp
    AbstractUI.h)

include(GNUInstallDirs)
install(TARGETS praktikum_2
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
