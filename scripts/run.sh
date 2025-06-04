#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Function to print usage
print_usage() {
    echo -e "${YELLOW}Usage:${NC}"
    echo "  ./run.sh [options] [program_name]"
    echo
    echo -e "${YELLOW}Options:${NC}"
    echo "  -h, --help     Show this help message"
    echo "  -l, --list     List all available programs"
    echo
    echo -e "${YELLOW}Example:${NC}"
    echo "  ./run.sh              # Run the first available program"
    echo "  ./run.sh program_name # Run a specific program"
    echo "  ./run.sh -l           # List all available programs"
}

# Function to list available programs
list_programs() {
    echo -e "${YELLOW}Available programs:${NC}"
    if [ -d "build" ]; then
        local found=false
        # Find all executables in build directory, excluding CMakeFiles
        for program in $(find build -type f -not -path "*/CMakeFiles/*" -not -path "*/\.*"); do
            if [ -x "$program" ]; then
                echo "  $(basename "$program")"
                found=true
            fi
        done
        if [ "$found" = false ]; then
            echo -e "${YELLOW}No executable programs found in build directory${NC}"
            echo -e "${YELLOW}Please run ./scripts/build.sh first${NC}"
        fi
    else
        echo -e "${RED}No build directory found. Please run ./scripts/build.sh first${NC}"
        exit 1
    fi
}

# Function to find first available executable
find_first_executable() {
    for program in $(find build -type f -not -path "*/CMakeFiles/*" -not -path "*/\.*"); do
        if [ -x "$program" ]; then
            echo "$program"
            return 0
        fi
    done
    return 1
}

# Default values
SHOW_LIST=false
PROGRAM_NAME=""

# Parse command line arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        -h|--help)
            print_usage
            exit 0
            ;;
        -l|--list)
            SHOW_LIST=true
            shift
            ;;
        *)
            if [ -z "$PROGRAM_NAME" ]; then
                PROGRAM_NAME="$1"
            else
                echo -e "${RED}Error: Unexpected argument '$1'${NC}"
                print_usage
                exit 1
            fi
            shift
            ;;
    esac
done

# If -l flag is set, just show the list and exit
if [ "$SHOW_LIST" = true ]; then
    list_programs
    exit 0
fi

# Find the program to run
PROGRAM_PATH=""
if [ -n "$PROGRAM_NAME" ]; then
    # Find specific program
    for program in $(find build -type f -not -path "*/CMakeFiles/*" -not -path "*/\.*"); do
        if [ -x "$program" ] && [ "$(basename "$program")" = "$PROGRAM_NAME" ]; then
            PROGRAM_PATH="$program"
            break
        fi
    done

    if [ -z "$PROGRAM_PATH" ]; then
        echo -e "${RED}Error: Program '$PROGRAM_NAME' not found in build directory${NC}"
        echo -e "${YELLOW}Available programs:${NC}"
        list_programs
        exit 1
    fi
else
    # Find first available executable
    PROGRAM_PATH=$(find_first_executable)
    if [ -z "$PROGRAM_PATH" ]; then
        echo -e "${RED}Error: No executable programs found in build directory${NC}"
        echo -e "${YELLOW}Please run ./scripts/build.sh first${NC}"
        exit 1
    fi
    PROGRAM_NAME=$(basename "$PROGRAM_PATH")
fi

# Run the program
echo -e "${YELLOW}Running $PROGRAM_NAME...${NC}"
"$PROGRAM_PATH" 