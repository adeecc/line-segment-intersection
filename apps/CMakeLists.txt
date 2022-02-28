cmake_minimum_required(VERSION 3.16.0)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  "${PROJECT_SOURCE_DIR}/bin")

add_executable(intersection_of_segments intersection_of_segments.cpp)
target_compile_features(intersection_of_segments PRIVATE cxx_std_17)

target_link_libraries(intersection_of_segments PRIVATE geometry ds)