cmake_minimum_required(VERSION 3.16.0)


# Testing Library
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
  )
  
FetchContent_MakeAvailable(googletest)
# Add GoogleTest

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  "${PROJECT_SOURCE_DIR}/bin/tests")
set(CMAKE_WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/tests")

# Tests need to be added as executables first
add_executable(testlib testlib.cpp)

# Using C++ 17 in the tests
target_compile_features(testlib PRIVATE cxx_std_17)

# Should be linked to the main library, as well as the Googletest testing library
target_link_libraries(testlib PRIVATE ds geometry gtest_main)

# If you register a test, then ctest and make test will run it.
# You can also run examples and check the output, as well.

add_test(NAME testlib COMMAND testlib) # Command can be a target