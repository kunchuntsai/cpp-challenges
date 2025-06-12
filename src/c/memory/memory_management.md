# Custom Memory Management & Safe String Operations

This example demonstrates the implementation of custom memory management and safe string operations in C.

## Concepts Demonstrated

1. **Custom Memory Management**
   - Custom memory allocator implementation (`custom_malloc`)
   - Custom memory deallocator implementation (`custom_free`)
   - Memory block management with linked list
   - Memory block splitting and coalescing
   - Static heap management

2. **Safe String Operations**
   - Bounds-checked string copy (`safe_strcpy`)
   - Length-limited string copy (`safe_strncpy`)
   - Buffer overflow prevention
   - Null pointer handling
   - String truncation handling

3. **Memory Management Features**
   - Memory block header structure
   - Free block tracking
   - Adjacent block coalescing
   - Memory fragmentation prevention
   - Size-based block splitting

## Implementation Details

1. **Memory Block Structure**
   ```c
   typedef struct MemoryBlock {
       size_t size;           // Size of the allocated block
       bool is_free;          // Whether the block is free
       struct MemoryBlock* next;  // Next block in the list
   } MemoryBlock;
   ```

2. **Memory Management Functions**
   - `init_memory_system()`: Initializes the memory system with a static heap
   - `custom_malloc(size_t size)`: Allocates memory blocks with size tracking
   - `custom_free(void* ptr)`: Frees memory and coalesces adjacent blocks

3. **Safe String Functions**
   - `safe_strcpy(dest, src, dest_size)`: Bounds-checked string copy
   - `safe_strncpy(dest, src, dest_size, n)`: Length-limited string copy

## Memory Management Algorithm

1. **Allocation Process**
   - Search for a suitable free block
   - Split block if large enough
   - Update block headers
   - Return pointer to usable memory

2. **Deallocation Process**
   - Mark block as free
   - Coalesce adjacent free blocks
   - Update block headers
   - Maintain free block list

## Safety Features

1. **Memory Safety**
   - NULL pointer checks
   - Size validation
   - Block boundary checking
   - Memory block integrity verification

2. **String Safety**
   - Buffer size validation
   - Null termination guarantee
   - Source string length checking
   - Destination buffer overflow prevention

## Learning Points

1. **Memory Management Best Practices**
   - Always track allocated block sizes
   - Implement proper block splitting
   - Coalesce adjacent free blocks
   - Handle memory fragmentation

2. **String Safety**
   - Always check buffer sizes
   - Guarantee null termination
   - Handle string truncation
   - Validate input parameters

3. **Debugging Tips**
   - Use memory debugging tools
   - Enable compiler warnings
   - Add debug logging
   - Test edge cases

## Example Usage

```c
// Initialize memory system
init_memory_system();

// Allocate memory
char* str = (char*)custom_malloc(50);
if (str) {
    // Safe string copy
    safe_strcpy(str, "Hello, World!", 50);

    // Use the string
    printf("%s\n", str);

    // Free memory
    custom_free(str);
}
```

## Additional Resources

- [Memory Management](https://en.wikipedia.org/wiki/Memory_management)
- [String Handling in C](https://en.wikipedia.org/wiki/C_string_handling)
- [Buffer Overflow](https://en.wikipedia.org/wiki/Buffer_overflow)
- [Memory Fragmentation](https://en.wikipedia.org/wiki/Fragmentation_(computing))