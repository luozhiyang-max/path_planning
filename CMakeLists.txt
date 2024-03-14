# cmake_minimum_required(VERSION <specify CMake version here>)
project(path_planning)

set(CMAKE_CXX_STANDARD 11)

set(SFML_DIR "D:/workSpace/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML REQUIRED COMPONENTS audio network graphics window system)

if (NOT SFML_FOUND)
    message(FATAL_ERROR "SFML NOT FOUND!")
else()
    message("SFML FOUND!")
endif()
include_directories(${SFML_INCLUDE_DIR})
add_executable(path_planning main.cpp grid.h
        A_star.h
        A_star.cpp
        ECBS.h
        ECBS.cpp)
target_link_libraries(path_planning sfml-audio sfml-network sfml-graphics sfml-window sfml-system)