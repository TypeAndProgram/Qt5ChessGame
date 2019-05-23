cmake_minimum_required(VERSION 3.10)
project(ChessGame)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Instruct CMake to run uic automatically when needed.
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED
    Core
    PrintSupport
    Gui
    Widgets
)
set(SOURCES src/chesspiece.cpp src/drawchessboard.cpp src/main.cpp src/mainwindow.cpp
src/validatepiecemove.cpp)
set(UI src/mainwindow.ui)

set(PCH_HEADER src/pch.h)

add_executable(ChessGame ${SOURCES} ${HEADERS} ${UI})

target_link_libraries(ChessGame Qt5::Widgets)
