# Fixed vs Dynamic Arrays in C

## Problem Description
Implement a program that demonstrates the key differences between fixed-size arrays (stack-allocated) and dynamic arrays (heap-allocated) in C. The program should:

1. Create and manipulate a fixed-size array
2. Create and manipulate a dynamic array
3. Demonstrate the advantages and limitations of each approach

### Requirements
1. Implement a function to create and initialize a fixed-size array
2. Implement a function to create and initialize a dynamic array
3. Implement functions to:
   - Add elements to both arrays
   - Remove elements from both arrays
   - Resize the dynamic array
   - Print the contents of both arrays
4. Handle memory management properly
5. Demonstrate error handling for both approaches

## Solution Approach

### Fixed Array Implementation
- Use a fixed-size array allocated on the stack
- Implement bounds checking
- Handle array full condition
- Demonstrate stack size limitations

### Dynamic Array Implementation
- Use malloc/realloc for heap allocation
- Implement automatic resizing
- Handle memory allocation failures
- Proper cleanup with free()

### Time and Space Complexity
- Fixed Array:
  - Time Complexity: O(1) for access, O(n) for insertion/deletion
  - Space Complexity: O(1) - fixed size
- Dynamic Array:
  - Time Complexity: O(1) for access, O(n) for insertion/deletion, O(n) for resizing
  - Space Complexity: O(n) - grows as needed

### Edge Cases to Handle
1. Stack overflow with large fixed arrays
2. Memory allocation failures
3. Array bounds violations
4. NULL pointer dereferencing
5. Memory leaks

## Common Mistakes to Avoid
1. Not checking malloc/realloc return values
2. Forgetting to free dynamically allocated memory
3. Buffer overflows in fixed arrays
4. Not handling reallocation failures
5. Memory leaks from improper cleanup

## Best Practices
1. Always validate array bounds
2. Use const for read-only parameters
3. Implement proper error handling
4. Document memory ownership
5. Use appropriate data types for sizes (size_t)
6. Consider using a struct to encapsulate array operations

## Learning Points
1. Stack vs Heap memory
2. Memory management in C
3. Array bounds checking
4. Error handling
5. Performance considerations
6. Memory safety

## Additional Resources
- [Stack vs Heap](https://en.wikipedia.org/wiki/Stack-based_memory_allocation)
- [Dynamic memory allocation](https://en.wikipedia.org/wiki/C_dynamic_memory_allocation)
- [Array data structure](https://en.wikipedia.org/wiki/Array_data_structure) 