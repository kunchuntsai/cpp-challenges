# Pointer Manipulation & Memory Management

This example demonstrates various concepts related to pointers and memory management in C.

## Concepts Demonstrated

1. **Proper Memory Management**
   - Dynamic memory allocation using `malloc`
   - Memory reallocation using `realloc`
   - Proper memory deallocation using `free`
   - NULL pointer checks
   - Memory allocation failure handling

2. **Pointer Arithmetic**
   - Array traversal using pointer arithmetic
   - Address manipulation
   - Pointer increment/decrement

3. **Multi-level Pointers**
   - Single pointer (`int*`)
   - Double pointer (`int**`)
   - Triple pointer (`int***`)
   - Dereferencing at different levels

4. **Common Pitfalls** (commented out in code)
   - Memory leaks
   - Dangling pointers
   - Buffer overflows

## Expected Output

The program will demonstrate:
1. Proper memory management with dynamic array allocation and resizing
2. Pointer arithmetic with array traversal
3. Multi-level pointer dereferencing

## Learning Points

1. **Memory Management Best Practices**
   - Always check if memory allocation was successful
   - Free allocated memory when no longer needed
   - Use `realloc` for resizing dynamic arrays
   - Handle memory allocation failures gracefully

2. **Pointer Safety**
   - Never dereference a NULL pointer
   - Don't use pointers after freeing their memory
   - Be careful with pointer arithmetic to avoid buffer overflows
   - Use appropriate pointer types and levels of indirection

3. **Debugging Tips**
   - Use tools like Valgrind to detect memory leaks
   - Enable compiler warnings (`-Wall -Wextra`)
   - Use debuggers to inspect pointer values and memory contents

## Additional Resources

- [C Programming Language](https://en.wikipedia.org/wiki/C_(programming_language))
- [Pointer (computer programming)](https://en.wikipedia.org/wiki/Pointer_(computer_programming))
- [Memory management](https://en.wikipedia.org/wiki/Memory_management) 