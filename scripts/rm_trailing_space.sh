#!/bin/bash

# Function to check if a command succeeded
check_error() {
    if [ $? -ne 0 ]; then
        echo "Error: $1"
        exit 1
    fi
}

# Function to remove trailing spaces from a file
remove_trailing_spaces() {
    local file="$1"
    if [ ! -f "$file" ]; then
        echo "Warning: '$file' is not a file"
        return 1
    fi

    # Skip binary files
    if file "$file" | grep -q "binary"; then
        echo "Skipping binary file: $file"
        return 0
    fi

    # Create a temporary file
    local temp_file=$(mktemp)
    check_error "Failed to create temporary file"

    # Remove trailing spaces and save to temp file
    sed 's/[[:space:]]*$//' "$file" > "$temp_file"
    check_error "Failed to process file: $file"

    # Check if the file was modified
    if ! cmp -s "$file" "$temp_file"; then
        # Replace original file with temp file
        mv "$temp_file" "$file"
        echo "Removed trailing spaces from: $file"
    else
        echo "No trailing spaces found in: $file"
        rm "$temp_file"
    fi
}

# Function to process files recursively
process_directory() {
    local dir="$1"
    local pattern="$2"
    
    # If the input is a file, process it directly
    if [ -f "$dir" ]; then
        remove_trailing_spaces "$dir"
        return
    fi

    # Process all files matching the pattern in current directory
    find "$dir" -type f -name "$pattern" | while read -r file; do
        remove_trailing_spaces "$file"
    done
}

# Default patterns for C++ files
CPP_PATTERNS=("*.cpp" "*.h" "*.hpp" "*.cc" "*.cxx" "*.hxx" "*.c" "*.h" "*.md")

# Check if any directories were provided
if [ $# -eq 0 ]; then
    echo "Usage: $0 <path1> [path2] [path3] ..."
    echo "Example: $0 src/ test/"
    echo "If no paths are provided, will process src/ and test/ directories"
    
    # Default to processing src/ and test/ directories
    DIRS=("src" "test")
else
    DIRS=("$@")
fi

# Process each path
for dir in "${DIRS[@]}"; do
    if [ ! -e "$dir" ]; then
        echo "Warning: Path '$dir' does not exist"
        continue
    fi
    
    echo "Processing path: $dir"
    for pattern in "${CPP_PATTERNS[@]}"; do
        process_directory "$dir" "$pattern"
    done
done

echo "Finished processing all files"
