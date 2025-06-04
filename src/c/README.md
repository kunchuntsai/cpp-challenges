# C Programming Practice

This directory contains focused C programming exercises organized into key practice areas to help improve C programming skills.

## Structure

- `memory/` - Pointer Manipulation & Memory Management
  - Dynamic memory allocation (malloc, calloc, free)
  - Pointer arithmetic and multi-level pointers
  - Common pitfalls: memory leaks, dangling pointers, buffer overflows

- `strings/` - String Processing
  - Manual string operations
  - Character array manipulation
  - Parsing and tokenization

- `arrays/` - Array & Buffer Operations
  - Array traversal and manipulation
  - Fixed-size vs dynamic arrays
  - Circular buffers (especially for embedded systems)

- `bits/` - Bit Manipulation
  - Bitwise operations (&, |, ^, ~, <<, >>)
  - Setting/clearing/toggling specific bits
  - Bit masking techniques

- `system/` - Low-Level System Concepts
  - Understanding of stack vs heap
  - Function pointers and callbacks
  - Basic understanding of memory layout

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