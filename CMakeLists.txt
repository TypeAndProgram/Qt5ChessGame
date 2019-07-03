cmake_minimum_required(VERSION 3.10)
project(ChessGame)

# Add path for modules
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Instruct CMake to run uic automatically when needed.
set(CMAKE_AUTOUIC ON)

# Set directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if (EXISTS "$LOC_PATH")
	message(FATAL_ERROR "You cannot build in a source directory (or any directory that contains
	a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt
	and CMakeFiles.")
endif()

find_package(PrecompiledHeader REQUIRED)
find_package(Qt5 REQUIRED
    Core
    PrintSupport
    Gui
    Widgets
)
set(SOURCES src/chesspiece.cpp src/chessboard.cpp src/main.cpp src/mainwindow.cpp
src/validatepiecemove.cpp)
set(UI src/mainwindow.ui)

add_executable(ChessGame ${SOURCES} ${HEADERS} ${UI})

add_precompiled_header(ChessGame include/ChessGame/pch.h FORCEINCLUDE)
target_link_libraries(ChessGame Qt5::Widgets)
