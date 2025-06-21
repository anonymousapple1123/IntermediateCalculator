cmake_minimum_required(VERSION 3.10)

project(test VERSION 1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Collect all .cpp source files
file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Define the executable target
add_executable(main ${SRC_FILES})

# Add include directories
target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/include)
