cmake_minimum_required(VERSION 3.23)
project(sudoku_solver_hack_cpp)

set(CMAKE_CXX_STANDARD 23)

add_executable(sudoku_solver_hack_cpp main.cpp)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(sudoku_solver_hack_cpp ${OpenCV_LIBS})
