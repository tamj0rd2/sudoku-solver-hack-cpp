cmake_minimum_required(VERSION 3.23)
project(sudoku_solver_hack_cpp)

set(CMAKE_CXX_STANDARD 23)

configure_file(Config.h.in ${CMAKE_BINARY_DIR}/Config.h)
include_directories(${CMAKE_BINARY_DIR})

add_executable(sudoku_solver_hack_cpp main.cpp)

target_compile_definitions(sudoku_solver_hack_cpp PUBLIC SUDOKU_IMG_PATH="${CMAKE_CURRENT_SOURCE_DIR}/sudoku.jpg")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(sudoku_solver_hack_cpp ${OpenCV_LIBS})
