# Memory Management Pitfalls in C

This document outlines common memory management pitfalls in C programming and provides solutions to avoid them. Understanding these patterns is crucial for writing robust and memory-safe C programs.

## Common Memory Management Issues

### 1. Basic Memory Leak
```c
void memory_leak_example() {
    int* ptr = (int*)malloc(sizeof(int));
    *ptr = 42;
    // Memory leak: forgot to free the memory
}
```
**Problem**: Memory is allocated but never freed.
**Solution**: Always pair `malloc()` with `free()`.

### 2. Double Free
```c
void double_free_example() {
    int* ptr = (int*)malloc(sizeof(int));
    free(ptr);
    free(ptr);  // Error: double free
}
```
**Problem**: Freeing the same memory twice can cause undefined behavior.
**Solution**: Free memory only once and set pointer to NULL after freeing.

### 3. Use After Free
```c
void use_after_free_example() {
    int* ptr = (int*)malloc(sizeof(int));
    free(ptr);
    *ptr = 100;  // Error: using memory after it's freed
}
```
**Problem**: Accessing memory after it's been freed leads to undefined behavior.
**Solution**: Never use a pointer after freeing it.

### 4. Memory Leak in Loop
```c
void memory_leak_in_loop() {
    for (int i = 0; i < 10; i++) {
        int* ptr = (int*)malloc(sizeof(int));
        *ptr = i;
        // Memory leak: new allocation in each iteration
    }
}
```
**Problem**: Memory is allocated in each iteration without being freed.
**Solution**: Free memory inside the loop or store pointers in an array.

### 5. Incorrect Array Allocation
```c
void incorrect_array_allocation() {
    int* arr = (int*)malloc(5);  // Error: should be 5 * sizeof(int)
}
```
**Problem**: Not allocating enough memory for arrays.
**Solution**: Always use `sizeof(type) * number_of_elements`.

### 6. Memory Leak in Error Handling
```c
void memory_leak_in_error_handling() {
    int* ptr1 = (int*)malloc(sizeof(int));
    if (ptr1 == NULL) {
        return;  // Memory leak: forgot to free ptr1
    }

    int* ptr2 = (int*)malloc(sizeof(int));
    if (ptr2 == NULL) {
        return;  // Memory leak: forgot to free ptr1 and ptr2
    }
}
```
**Problem**: Not freeing memory when errors occur.
**Solution**: Free all previously allocated memory before returning on error.

### 7. String Memory Management
```c
void string_memory_management() {
    char* str = (char*)malloc(6);
    strcpy(str, "Hello");
    str = "World";  // Memory leak: lost reference to allocated memory
}
```
**Problem**: Losing reference to allocated string memory.
**Solution**: Free memory before reassignment or use `strncpy`.

## Best Practices

1. **Initialize Pointers**
   - Always initialize pointers to NULL
   - Check return values from memory allocation functions

2. **Memory Allocation**
   - Use `sizeof` operator with `malloc`
   - Check for NULL returns from allocation functions
   - Consider using `calloc` for zero-initialized memory

3. **Memory Deallocation**
   - Free memory in the reverse order of allocation
   - Set pointers to NULL after freeing
   - Don't free NULL pointers

4. **Error Handling**
   - Implement proper error handling for memory allocation
   - Free all allocated memory before returning on error
   - Use consistent error handling patterns

5. **String Management**
   - Use `strncpy` instead of `strcpy`
   - Always null-terminate strings
   - Free string memory before reassignment

## Tools for Memory Management

1. **Valgrind**
   - Use for memory leak detection
   - Command: `valgrind --leak-check=full ./your_program`

2. **AddressSanitizer (ASan)**
   - Compile with: `-fsanitize=address`
   - Detects memory errors at runtime

3. **Static Analysis Tools**
   - Clang Static Analyzer
   - Coverity
   - PVS-Studio

## Example of Proper Memory Management

```c
void proper_memory_management() {
    int* ptr = NULL;

    // Initialize pointer
    ptr = (int*)malloc(sizeof(int));
    if (ptr == NULL) {
        // Handle allocation failure
        return;
    }

    // Use the memory
    *ptr = 42;

    // Free the memory
    free(ptr);
    ptr = NULL;
}
```

## Common Pitfalls to Avoid

1. Forgetting to free memory
2. Double freeing memory
3. Using memory after freeing it
4. Not checking allocation failures
5. Incorrect size calculations
6. Memory leaks in error paths
7. Not handling string termination properly
8. Forgetting to free memory in loops

## Additional Resources

1. [C Memory Management](https://en.wikipedia.org/wiki/C_dynamic_memory_allocation)
2. [Valgrind Documentation](https://valgrind.org/docs/manual/manual.html)
3. [AddressSanitizer](https://clang.llvm.org/docs/AddressSanitizer.html)