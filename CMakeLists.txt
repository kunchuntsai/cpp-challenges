cmake_minimum_required(VERSION 3.10)
project(CppChallenges VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include the header files
include_directories(include)

# Add all source files
file(GLOB SOURCES "src/*.cc")

# Add all test files
file(GLOB TEST_SOURCES "test/*.cc")

# Find the threading library
find_package(Threads REQUIRED)

# Create the executable
add_executable(cpp-challenges ${SOURCES} ${TEST_SOURCES})

# Link the threading library
target_link_libraries(cpp-challenges PRIVATE Threads::Threads)