#!/bin/bash

# Default values
DEBUG=false
CLEAN=false
TARGET=""
COMPILER="gcc"
FLAGS="-Wall -Wextra -pthread"
BUILD_DIR="build"

# Help message
show_help() {
    echo "Usage: ./build_c.sh [options] [target]"
    echo "Options:"
    echo "  -d, --debug     Build with debug flags (-g)"
    echo "  -c, --clean     Clean build directory before building"
    echo "  -h, --help      Show this help message"
    echo "  -t, --target    Specify target directory to build"
    echo "Example: ./build_c.sh -d -t c-practice/memory/pointer_basics"
}

# Parse command line arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        -d|--debug)
            DEBUG=true
            shift
            ;;
        -c|--clean)
            CLEAN=true
            shift
            ;;
        -h|--help)
            show_help
            exit 0
            ;;
        -t|--target)
            TARGET="$2"
            shift 2
            ;;
        *)
            echo "Unknown option: $1"
            show_help
            exit 1
            ;;
    esac
done

# Add debug flags if requested
if [ "$DEBUG" = true ]; then
    FLAGS="$FLAGS -g"
fi

# Function to build a single program
build_program() {
    local dir=$1
    
    # Find all .c files in the directory and its immediate subdirectories
    local source_files=$(find "$dir" -maxdepth 2 -name "*.c")
    
    if [ -z "$source_files" ]; then
        echo "No .c files found in $dir or its subdirectories"
        return 1
    fi
    
    # Build each .c file found
    for source_file in $source_files; do
        local program_name=$(basename "$source_file" .c)
        local category_name=$(basename "$(dirname "$source_file")")
        local build_path="$BUILD_DIR/$category_name"
        
        # Create build directory if it doesn't exist
        mkdir -p "$build_path"
        
        echo "Building $program_name..."
        $COMPILER $FLAGS -o "$build_path/$program_name" "$source_file"
        
        if [ $? -eq 0 ]; then
            echo "Successfully built $program_name"
        else
            echo "Failed to build $program_name"
            return 1
        fi
    done
}

# Clean build directory if requested
if [ "$CLEAN" = true ]; then
    echo "Cleaning build directory..."
    rm -rf "$BUILD_DIR"
fi

# Create build directory if it doesn't exist
mkdir -p "$BUILD_DIR"

# Build target or all programs
if [ -n "$TARGET" ]; then
    if [ -d "$TARGET" ]; then
        build_program "$TARGET"
    else
        echo "Target directory $TARGET does not exist"
        exit 1
    fi
else
    # Build all programs in all subdirectories
    for dir in src/c/memory src/c/strings src/c/arrays src/c/bits src/c/system src/c/test; do
        if [ -d "$dir" ]; then
            build_program "$dir"
        fi
    done

    # Build the generic runner
    echo "Building generic runner..."
    $COMPILER $FLAGS -o "$BUILD_DIR/run_all" src/c/run_all.c
    if [ $? -eq 0 ]; then
        echo "Successfully built generic runner"
    else
        echo "Failed to build generic runner"
        exit 1
    fi
fi 