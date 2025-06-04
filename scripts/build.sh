#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Function to print usage
print_usage() {
    echo -e "${YELLOW}Usage:${NC}"
    echo "  ./build.sh [options]"
    echo
    echo -e "${YELLOW}Options:${NC}"
    echo "  -h, --help     Show this help message"
    echo "  -c, --clean    Clean build artifacts"
    echo "  -r, --run      Run the program after building"
    echo "  -d, --debug    Build with debug flags"
    echo
    echo -e "${YELLOW}Example:${NC}"
    echo "  ./build.sh -r    # Build and run"
    echo "  ./build.sh -d    # Build with debug flags"
}

# Default values
CLEAN=false
RUN=false
DEBUG=false

# Parse command line arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        -h|--help)
            print_usage
            exit 0
            ;;
        -c|--clean)
            CLEAN=true
            shift
            ;;
        -r|--run)
            RUN=true
            shift
            ;;
        -d|--debug)
            DEBUG=true
            shift
            ;;
        *)
            echo -e "${RED}Unknown option: $1${NC}"
            print_usage
            exit 1
            ;;
    esac
done

# Create build directory if it doesn't exist
mkdir -p build

# Clean build directory if requested
if [ "$CLEAN" = true ]; then
    echo -e "${YELLOW}Cleaning build directory...${NC}"
    rm -rf build/*
fi

# Configure CMake
echo -e "${YELLOW}Configuring CMake...${NC}"
if [ "$DEBUG" = true ]; then
    cmake -B build -DCMAKE_BUILD_TYPE=Debug
else
    cmake -B build -DCMAKE_BUILD_TYPE=Release
fi

if [ $? -ne 0 ]; then
    echo -e "${RED}CMake configuration failed${NC}"
    exit 1
fi

# Build the project
echo -e "${YELLOW}Building project...${NC}"
cmake --build build

if [ $? -ne 0 ]; then
    echo -e "${RED}Build failed${NC}"
    exit 1
fi

echo -e "${GREEN}Build completed successfully!${NC}"

# Run the program if requested
if [ "$RUN" = true ]; then
    # Find the executable
    EXECUTABLE=$(find build -type f -executable -not -path "*/CMakeFiles/*" | head -n 1)
    if [ -n "$EXECUTABLE" ]; then
        echo -e "${YELLOW}Running $EXECUTABLE...${NC}"
        "$EXECUTABLE"
    else
        echo -e "${RED}No executable found to run${NC}"
        exit 1
    fi
fi 