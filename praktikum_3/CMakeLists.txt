cmake_minimum_required(VERSION 3.5)

project(praktikum_3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(praktikum_3 main.cpp
    Tile.cpp
    Tile.h
    Character.h
    Character.cpp
    Level.cpp
    Level.h
    DungeonCrawler.cpp
    DungeonCrawler.h
    AbstractUI.cpp
    AbstractUI.h
    Floor.cpp
    Floor.h
    Wall.h
    Wall.cpp
    Portal.cpp
    Portal.h
    TerminalUI.cpp
    TerminalUI.h
    Passive.h
    Aktive.h
    Aktive.cpp
    Passive.cpp
    Switch.cpp
    Switch.h
    Door.cpp
    Door.h
    Pit.cpp
    Pit.h
    Ramp.cpp
    Ramp.h)

include(GNUInstallDirs)
install(TARGETS praktikum_3
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
