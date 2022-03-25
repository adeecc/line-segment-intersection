cmake_minimum_required(VERSION 3.16.0)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  "${PROJECT_SOURCE_DIR}/bin")

add_executable(
    main 
    main.cpp
)

target_compile_features(main PRIVATE cxx_std_20)
target_link_libraries(main PRIVATE sweep_line)

target_include_directories(
    main
    PUBLIC
    include/
)