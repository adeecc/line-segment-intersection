cmake_minimum_required(VERSION 3.16.0)


# Testing Library
FetchContent_Declare(
  benchmark
  URL https://github.com/google/benchmark/archive/refs/tags/v1.6.1.zip
)
  
FetchContent_MakeAvailable(benchmark)
# Add GoogleTest

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  "${PROJECT_SOURCE_DIR}/bin")

# Tests need to be added as executables first
add_executable(benchmark_sweepline 
  sweep_line.cpp 
)

# Using C++ 17 in the tests
target_compile_features(benchmark_sweepline PRIVATE cxx_std_20)

# Should be linked to the main library, as well as the Googletest testing library
target_link_libraries(benchmark_sweepline PRIVATE sweep_line benchmark::benchmark)

# If you register a test, then ctest and make test will run it.
# You can also run examples and check the output, as well.

add_test(NAME benchmark_sweepline COMMAND benchmark_sweepline) # Command can be a target