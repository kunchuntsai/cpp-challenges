cmake_minimum_required(VERSION 3.10)
project(CppChallenges VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include the header files
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/include
)

# Find the threading library
find_package(Threads REQUIRED)

# Add all test files from src/cpp/arrays_hashing
file(GLOB ARRAY_HASHING_TESTS "src/cpp/arrays_hashing/*_test.cpp")

# Create separate executables for each array hashing test
foreach(test_file ${ARRAY_HASHING_TESTS})
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(${test_name} ${test_file})
    target_link_libraries(${test_name} PRIVATE Threads::Threads)
endforeach()

# Add all other test files
file(GLOB TEST_SOURCES "test/*.cc")

# Create the main test executable
add_executable(cpp-challenges ${TEST_SOURCES})
target_link_libraries(cpp-challenges PRIVATE Threads::Threads)