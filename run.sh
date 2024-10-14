#!/bin/bash

# Check if build directory exists
if [ -d "build" ]; then
    echo "Build directory already exists. Cleaning..."
    rm -rf build/*
else
    echo "Creating build directory..."
    mkdir build
fi

# Navigate to build directory
cd build

# Run CMake and make
cmake ..
make

# Run the executable
./cpp-challenges