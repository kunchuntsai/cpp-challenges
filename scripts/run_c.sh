#!/bin/bash

# Default values
LIST=false
TARGET=""
BUILD_DIR="build"

# Help message
show_help() {
    echo "Usage: ./run_c.sh [options] [target]"
    echo "Options:"
    echo "  -l, --list      List all available programs"
    echo "  -h, --help      Show this help message"
    echo "  -a, --all       Run all programs using the generic runner"
    echo "Example: ./run_c.sh pointer_demo"
    echo "         ./run_c.sh -a"
    echo "         ./run_c.sh (runs all programs by default)"
}

# Parse command line arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        -l|--list)
            LIST=true
            shift
            ;;
        -h|--help)
            show_help
            exit 0
            ;;
        -a|--all)
            if [ -x "$BUILD_DIR/run_all" ]; then
                "$BUILD_DIR/run_all"
                exit 0
            else
                echo "Generic runner not found. Please build it first using ./scripts/build_c.sh"
                exit 1
            fi
            ;;
        *)
            if [ -z "$TARGET" ]; then
                TARGET="$1"
            else
                echo "Unknown option: $1"
                show_help
                exit 1
            fi
            shift
            ;;
    esac
done

# Function to list all available programs
list_programs() {
    echo "Available programs:"
    # List the generic runner if it exists
    if [ -x "$BUILD_DIR/run_all" ]; then
        echo "  run_all (generic runner)"
    fi
    
    # List all other programs by recursively searching the build directory
    find "$BUILD_DIR" -type f -not -path "*/\.*" | while read -r program; do
        # Check if file is executable
        if [ -x "$program" ] && [ "$(basename "$program")" != "run_all" ]; then
            echo "  $(basename "$program")"
        fi
    done
}

# Function to run a program
run_program() {
    local target=$1
    local program_path=""
    
    # Check if it's the generic runner
    if [ "$target" = "run_all" ]; then
        if [ -x "$BUILD_DIR/run_all" ]; then
            "$BUILD_DIR/run_all"
            return 0
        else
            echo "Generic runner not found. Please build it first using ./scripts/build_c.sh"
            return 1
        fi
    fi
    
    # First check if the program exists directly in the build directory
    if [ -x "$BUILD_DIR/$target" ]; then
        program_path="$BUILD_DIR/$target"
    else
        # Find the program in subdirectories of the build directory
        for dir in "$BUILD_DIR"/*; do
            if [ -d "$dir" ]; then
                if [ -x "$dir/$target" ]; then
                    program_path="$dir/$target"
                    break
                fi
            fi
        done
    fi
    
    if [ -n "$program_path" ]; then
        echo "Running $target..."
        "$program_path"
    else
        echo "Program $target not found or not executable"
        exit 1
    fi
}

# List programs if requested
if [ "$LIST" = true ]; then
    list_programs
    exit 0
fi

# Run target or run_all by default
if [ -n "$TARGET" ]; then
    run_program "$TARGET"
else
    # Run run_all by default
    if [ -x "$BUILD_DIR/run_all" ]; then
        "$BUILD_DIR/run_all"
    else
        echo "Generic runner not found. Please build it first using ./scripts/build_c.sh"
        exit 1
    fi
fi 