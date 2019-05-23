cmake_minimum_required(VERSION 3.10)

project(ChessGame) # Your project name

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Instruct CMake to run uic automatically when needed.
set(CMAKE_AUTOUIC ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

# This will find the Qt5 files. You will need a QT5_DIR env variable
#  find_package(Qt5Widgets REQUIRED) # Equivalent of QT += widgets
#  find_package(QtCore REQUIRED)
#  find_package(QtGui REQUIRED)

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

# This will create you executable
add_executable(ChessGame ${SOURCES} ${HEADERS} ${UI})
# This will link necessary Qt5 libraries to your project
target_link_libraries(ChessGame Qt5::Widgets)
