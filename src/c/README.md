# C Programming Practice

This directory contains focused C programming exercises organized into key practice areas to help improve C programming skills.

## Structure

`memory/` - Pointer Manipulation & Memory Management
- [pointer_demo.c](memory/pointer_demo.c) - Dynamic memory allocation, pointer arithmetic, and multi-level pointers with proper memory management practices
- [memory_management.c](memory/memory_management.c) - Custom memory allocator implementation with safe string operations and memory block management
- [memory_management_pitfalls.c](memory/memory_management_pitfalls.c) - Common memory management pitfalls and their solutions
- [raii_patterns.c](memory/raii_patterns.c) - Resource Acquisition Is Initialization (RAII) patterns in C

`strings/` - String Processing
- [string_processing.c](strings/string_processing.c) - Manual string operations, character array manipulation, and string tokenization with memory safety

`arrays/` - Array & Buffer Operations
- [array_operations.c](arrays/array_operations.c) - Fixed-size arrays, dynamic arrays with automatic growth, and circular buffer implementation
- [max_subarray.c](arrays/max_subarray.c) - Implementation of Kadane's algorithm for finding the maximum sum subarray with index tracking

`bits/` - Bit Manipulation
- [bit_operations.c](bits/bit_operations.c) - Bitwise operations, bit masking, and bit manipulation algorithms with best practices
- [bit_swap.c](bits/bit_swap.c) - Efficient bit swapping algorithms and bit manipulation techniques

`system/` - Low-Level System Concepts
- [system_concepts.c](system/system_concepts.c) - Stack vs heap memory, function pointers, and program memory layout with safety considerations

## How to Build and Run

The project includes build and run scripts in the `scripts/` directory. All programs are built into a single `build/` directory at the root level, maintaining the same directory structure as the source code.

```bash
# Build all programs
../../scripts/build_c.sh

# Build a specific program
../../scripts/build_c.sh -t src/c/memory/pointer_demo

# Build with debug flags
../../scripts/build_c.sh -d -t src/c/memory/pointer_demo

# Clean and rebuild
../../scripts/build_c.sh -c -t src/c/memory/pointer_demo

# Run a specific program
../../scripts/run_c.sh -t pointer_demo

# Run all programs using the generic runner
../../scripts/run_c.sh -a

# List all available programs
../../scripts/run_c.sh -l
```

## Prerequisites

- GCC or Clang compiler
- Basic understanding of C programming concepts

## Getting Started

1. Start with the exercises in the `memory/` directory to understand fundamental concepts
2. Progress through `strings/` and `arrays/` to build practical skills
3. Move on to `bits/` for low-level operations
4. Finally, explore `system/` for deeper system-level understanding

## Best Practices

- Always include proper error handling
- Use meaningful variable and function names
- Comment your code appropriately
- Follow C programming standards and conventions
- Test your code thoroughly
- Use memory debugging tools (e.g., Valgrind) when working with dynamic memory 