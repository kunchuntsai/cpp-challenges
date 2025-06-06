# Low-Level System Concepts in C

This document covers fundamental low-level system concepts in C programming, including memory management, function pointers, and system-level programming.

## Key Concepts

### 1. Stack vs Heap Memory

#### Stack Memory
- Automatic memory management
- Limited size
- Fast allocation/deallocation
- LIFO (Last In, First Out) structure
- Used for local variables and function calls

#### Heap Memory
- Manual memory management
- Larger size
- Slower allocation/deallocation
- Dynamic allocation
- Used for long-lived data and large objects

### 2. Function Pointers and Callbacks

#### Function Pointer Syntax
```c
// Function pointer type definitions
typedef void (*Operation)(int);
typedef int (*Comparator)(const void*, const void*);
typedef void (*StringProcessor)(char*);

// Function pointer variable
Operation op = &some_function;
```

#### Common Uses
- Callback mechanisms
- State machines
- Plugin architectures
- Event handling systems
- String processing pipelines
- Dynamic function selection

### 3. Memory Layout

#### Program Memory Segments
1. **Text Segment**
   - Contains executable code
   - Read-only
   - Shared between processes

2. **Data Segment**
   - Static/global variables
   - Initialized data
   - Uninitialized data (BSS)

3. **Heap**
   - Dynamic memory allocation
   - Grows upward

4. **Stack**
   - Local variables
   - Function parameters
   - Return addresses
   - Grows downward

#### Structure Memory Layout
- Member alignment and padding
- Bit fields for memory optimization
- Endianness considerations
- Cache-friendly data structures

## Example Code

The `system_concepts.c` example demonstrates:

1. **Function Pointers and Callbacks**
   - Basic function pointer usage
   - String processing with function pointers
   - Array of function pointers
   - Type definitions for function pointers

2. **Stack vs Heap Memory**
   - Stack variable allocation
   - Heap memory allocation with error checking
   - Memory leak demonstration
   - Proper memory cleanup

3. **Memory Layout**
   - Structure padding and alignment
   - Bit fields usage
   - Endianness detection
   - Member size and address visualization

## Best Practices

### Memory Management
1. Always free heap-allocated memory
2. Check for NULL after malloc
3. Use appropriate memory allocation functions
4. Avoid memory leaks
5. Be aware of stack limitations
6. Handle allocation failures gracefully

### Function Pointers
1. Use typedef for complex function pointer types
2. Check for NULL before calling
3. Document callback signatures
4. Consider function pointer safety
5. Use appropriate calling conventions
6. Group related function pointers in arrays

### Memory Layout
1. Be aware of alignment requirements
2. Consider padding in structures
3. Understand memory model
4. Account for endianness
5. Consider cache effects
6. Use bit fields for memory optimization

## Common Pitfalls

1. **Memory Management**
   - Memory leaks
   - Double free
   - Use after free
   - Buffer overflows
   - Stack overflow
   - Unchecked malloc returns

2. **Function Pointers**
   - Calling through NULL pointer
   - Wrong function signature
   - Incorrect calling convention
   - Type mismatches
   - Undefined behavior
   - Array bounds checking

3. **Memory Layout**
   - Alignment issues
   - Padding surprises
   - Endianness problems
   - Cache misses
   - Memory fragmentation
   - Bit field overflow

## Running the Examples

To compile and run the examples:
```bash
gcc -o system_concepts system_concepts.c
./system_concepts
```

The program will demonstrate:
1. Function pointer usage with string processing
2. Stack vs heap memory allocation
3. Memory layout visualization
4. Endianness detection
5. Bit field usage 