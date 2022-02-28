cmake_minimum_required(VERSION 3.16.0)

file (GLOB_RECURSE HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/*.hpp")
file (GLOB_RECURSE SOURCES_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/lib/*.cpp")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  "${PROJECT_SOURCE_DIR}/bin/lib")

# Make an automatic library - will be static or dynamic based on user setting
add_library(ds ${SOURCES_LIST} ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(ds PUBLIC "${PROJECT_SOURCE_DIR}/include")

# All users of this library will need at least C++17
target_compile_features(ds PUBLIC cxx_std_17)

# IDEs should put the headers in a nice place
source_group(
    TREE "${PROJECT_SOURCE_DIR}/include"
    PREFIX "Header Files"
    FILES ${HEADER_LIST}
)