cmake_minimum_required(VERSION 3.16.0)

project(sweep_line VERSION 0.1.0 LANGUAGES CXX)

# Make an automatic library - will be static or dynamic based on user setting
add_library(
    sweep_line 
    STATIC
    src/line_segment.cpp
    src/event_queue.cpp
    src/line_sweep.cpp
)

# All users of this library will need at least C++20
target_compile_features(sweep_line PUBLIC cxx_std_20)

# We need this directory, and users of our library will need it too
target_include_directories(
    sweep_line
    PUBLIC
    include/
)