# C Programming Practice

This directory contains focused C programming exercises organized into key practice areas to help improve C programming skills.

## Practices

`arrays/` - Array & Buffer Operations
- [bounds_checking.c](arrays/bounds_checking.c) - Safe string operations with bounds checking and buffer overflow prevention
- [circular_buffer.c](arrays/circular_buffer.c) - Fixed-size arrays, dynamic arrays with automatic growth, and circular buffer implementation
- [fixed_vs_dynamic.c](arrays/fixed_vs_dynamic.c) - Comprehensive comparison of stack vs heap arrays, memory management, and performance characteristics
- [max_subarray.c](arrays/max_subarray.c) - Implementation of Kadane's algorithm for finding the maximum sum subarray with index tracking
- [secure_bounds_checking.c](arrays/secure_bounds_checking.c) - Advanced secure array implementation with comprehensive safety features

`bits/` - Bit Manipulation
- [bit_operations.c](bits/bit_operations.c) - Bitwise operations, bit masking, and bit manipulation algorithms with best practices
- [bit_swap.c](bits/bit_swap.c) - Efficient bit swapping algorithms and bit manipulation techniques

`memory/` - Memory Management & Pointer Concepts
- [double_pointers.c](memory/double_pointers.c) - Advanced pointer concepts with double pointers, including dynamic 2D arrays, linked lists, and function pointer arrays
- [memory_management.c](memory/memory_management.c) - Custom memory allocator implementation with safe string operations and memory block management
- [memory_pitfalls.c](memory/memory_pitfalls.c) - Common memory management pitfalls and their solutions, including memory leaks and buffer overflows
- [raii_patterns.c](memory/raii_patterns.c) - Resource Acquisition Is Initialization (RAII) patterns in C

`strings/` - String Processing
- [string_processing.c](strings/string_processing.c) - Manual string operations, character array manipulation, and string tokenization with memory safety

`system/` - Low-Level System Concepts
- [system_concepts.c](system/system_concepts.c) - Comprehensive coverage of low-level C concepts including:
  - Function pointers and callbacks with practical examples
  - Stack vs heap memory management with error handling
  - Memory layout visualization and bit fields
  - Endianness detection and structure padding
  - Memory safety and best practices

## Top 5 C Coding Skills for Interviews

**1. Pointer Manipulation & Memory Management**

- Dynamic memory allocation (malloc, calloc, free)
- Pointer arithmetic and multi-level pointers
- Common pitfalls: memory leaks, dangling pointers, buffer overflows

**2. String Processing**

- Manual string operations (since C has limited built-in string functions)
- Character array manipulation
- Parsing and tokenization

**3. Array & Buffer Operations**

- Array traversal and manipulation
- Fixed-size vs dynamic arrays
- Circular buffers (especially for embedded systems)

**4. Bit Manipulation**

- Bitwise operations (&, |, ^, ~, <<, >>)
- Setting/clearing/toggling specific bits
- Bit masking techniques

**5. Low-Level System Concepts**

- Understanding of stack vs heap
- Function pointers and callbacks
- Basic understanding of memory layout

## Typical C Coding Test Questions

### General Programming Questions:

- Implement string reversal without using library functions
- Find duplicates in an array using minimal extra space
- Implement a simple hash table with collision handling
- Write a function to detect if a linked list has a cycle
- Implement basic sorting algorithms (bubble, selection, insertion)

### Embedded Systems Focus:

- Write an interrupt service routine template
- Implement a circular buffer for sensor data
- Create a state machine for device control
- Write bit manipulation functions for register operations
- Implement a simple scheduler or task switcher

### Memory Management:

- Fix memory leaks in provided code
- Implement a custom malloc/free
- Debug pointer-related errors
- Write safe string copy functions

### Practical System Programming:

- Parse command-line arguments
- Implement file I/O operations with error handling
- Write functions to manipulate binary data
- Create producer-consumer patterns

## How to Build and Run

The project includes build and run scripts in the `scripts/` directory. All programs are built into a single `build/` directory at the root level, maintaining the same directory structure as the source code.

```bash
# Build all programs
../../scripts/build_c.sh

# Build a specific program
../../scripts/build_c.sh src/c/memory/pointer_demo

# Build with debug flags
../../scripts/build_c.sh -d src/c/memory/pointer_demo

# Clean and rebuild
../../scripts/build_c.sh -c src/c/memory/pointer_demo

# Run a specific program
../../scripts/run_c.sh pointer_demo

# Run all programs using the generic runner
../../scripts/run_c.sh -a

# List all available programs
../../scripts/run_c.sh -l
```

## Best Practices

- Always include proper error handling
- Use meaningful variable and function names
- Comment your code appropriately
- Follow C programming standards and conventions
- Test your code thoroughly
- Use memory debugging tools (e.g., Valgrind) when working with dynamic memory
- Implement proper memory cleanup in all code paths
- Validate pointer operations and array bounds
- Use assertions for debugging and validation
- Consider memory layout and alignment
- Be aware of endianness in data structures
- Use bit fields for memory optimization
- Group related function pointers in arrays 