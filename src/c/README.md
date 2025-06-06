# C Programming Practice

This directory contains focused C programming exercises organized into key practice areas to help improve C programming skills.

## Structure

`arrays/` - Array & Buffer Operations
- [circular_buffer.c](arrays/circular_buffer.c) - Fixed-size arrays, dynamic arrays with automatic growth, and circular buffer implementation
- [max_subarray.c](arrays/max_subarray.c) - Implementation of Kadane's algorithm for finding the maximum sum subarray with index tracking
- [fixed_vs_dynamic.c](arrays/fixed_vs_dynamic.c) - Comprehensive comparison of stack vs heap arrays, memory management, and performance characteristics
- [bounds_checking.c](arrays/bounds_checking.c) - Safe string operations with bounds checking and buffer overflow prevention
- [secure_bounds_checking.c](arrays/secure_bounds_checking.c) - Advanced secure array implementation with comprehensive safety features

`bits/` - Bit Manipulation
- [bit_operations.c](bits/bit_operations.c) - Bitwise operations, bit masking, and bit manipulation algorithms with best practices
- [bit_swap.c](bits/bit_swap.c) - Efficient bit swapping algorithms and bit manipulation techniques

`memory/` - Memory Management & Pointer Concepts
- [memory_management.c](memory/memory_management.c) - Custom memory allocator implementation with safe string operations and memory block management
- [memory_pitfalls.c](memory/memory_pitfalls.c) - Common memory management pitfalls and their solutions, including memory leaks and buffer overflows
- [double_pointers.c](memory/double_pointers.c) - Advanced pointer concepts with double pointers, including dynamic 2D arrays, linked lists, and function pointer arrays
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

## Core C Programming Challenges

The exercises in this repository focus on four fundamental C programming challenges:

1. **Memory Leak Detection**
   - Understanding malloc/free lifecycle
   - Memory leak detection tools (Valgrind, ASan)
   - Common memory leak patterns and solutions
   - Resource cleanup in error paths

2. **Double Pointers**
   - Modifying pointers themselves
   - Dynamic 2D array allocation
   - Linked list node manipulation
   - Function pointer arrays
   - String array management

3. **Buffer Overflow Prevention**
   - Safe string operations
   - Bounds checking
   - Buffer size validation
   - String truncation handling
   - Integer overflow prevention
   - Use-after-free detection
   - Secure memory management

4. **Array Safety and Performance**
   - Fixed vs dynamic array trade-offs
   - Circular buffer implementation
   - Memory layout optimization
   - Cache-friendly array access
   - Thread safety considerations

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

1. Start with the exercises in the `memory/` directory to understand fundamental concepts:
   - Begin with `memory_pitfalls.c` to learn common memory issues
   - Move to `double_pointers.c` for advanced pointer concepts
   - Study `memory_management.c` for custom memory handling
   - Finally, explore `raii_patterns.c` for resource management

2. Progress through `arrays/` to build practical skills:
   - Start with `fixed_vs_dynamic.c` to understand array types
   - Move to `bounds_checking.c` for basic safety
   - Study `secure_bounds_checking.c` for advanced safety
   - Explore `circular_buffer.c` for specialized implementations
   - Finally, try `max_subarray.c` for algorithm practice

3. Continue with `strings/` for text processing
4. Move on to `bits/` for low-level operations
5. Finally, explore `system/` for deeper system-level understanding:
   - Study `system_concepts.c` for comprehensive low-level concepts
   - Read `system_concepts.md` for detailed explanations
   - Practice with the provided examples
   - Experiment with the code to understand each concept

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