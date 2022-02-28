cmake_minimum_required(VERSION 3.16.0)

# Define the Project Name and Description
project(
    DAA_Assignments 
    VERSION 0.1.0
    LANGUAGES CXX 
    DESCRIPTION "All Assignments for CS F364: Design and Analysis of Algorithms AY 2021-22 Sem II")


if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

    # Set required C++ Standard
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    # Let's ensure -std=c++xx instead of -std=g++xx
    set(CMAKE_CXX_EXTENSIONS OFF)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

    # Let's nicely support folders in IDEs
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    # Testing only available if this is the main app
    # Note this needs to be done in the main CMakeLists
    # since it calls enable_testing, which must be in the
    # main CMakeLists.
    include(CTest)
endif()

# FetchContent added in CMake 3.11, downloads during the configure step
include(FetchContent)

# The compiled library code is here
add_subdirectory(lib)

# The executable code is here
add_subdirectory(apps)

# The testing code is here
add_subdirectory(tests)
