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

#### Comparator Example
```c
// Comparison function for integers
int compare_ints(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// Usage with qsort
int numbers[] = {5, 2, 8, 1, 9, 3};
int num_count = sizeof(numbers) / sizeof(numbers[0]);
qsort(numbers, num_count, sizeof(int), compare_ints);
```

The `Comparator` type is commonly used with sorting functions like `qsort`. The comparison function:
- Takes two `const void*` parameters for generic type support
- Returns negative if a < b, 0 if equal, positive if a > b
- Is used as a callback by the sorting algorithm

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

#### Finding Structure Size Without sizeof
Understanding structure size without using sizeof requires deep knowledge of:
- How structures are laid out in memory
- Memory alignment and padding rules
- Pointer arithmetic to calculate offsets

Common approaches to calculate structure size:

1. **Using Pointer Arithmetic**
```c
struct MyStruct {
    int a;
    char b;
    double c;
};

// Calculate size using pointer arithmetic
int getStructSize() {
    struct MyStruct *ptr = NULL;
    return (char*)(ptr + 1) - (char*)ptr;
}
```

2. **Using Array Indexing**
```c
int getStructSize2() {
    struct MyStruct arr[2];
    return (char*)&arr[1] - (char*)&arr[0];
}
```

This type of problem tests understanding of:
- Memory alignment
- Structure padding
- Pointer arithmetic
- Low-level memory concepts

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

## Bubble Sort Algorithm

Bubble sort is one of the simplest sorting algorithms. It's called "bubble sort" because smaller elements "bubble up" to the top of the array during each pass.

### Implementation
```c
void bubble_sort(int arr[], int size, Comparator compare) {
    for (int i = 0; i < size - 1; i++) {           // Outer loop: number of passes
        for (int j = 0; j < size - i - 1; j++) {   // Inner loop: compare adjacent elements
            // Use the comparison function pointer
            if (compare(&arr[j], &arr[j + 1]) > 0) {  // If elements are in wrong order
                // Swap elements
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
```

### How It Works
1. Start at the beginning of the array
2. Compare each pair of adjacent elements
3. If they are in the wrong order, swap them
4. Move to the next pair
5. Repeat until no more swaps are needed

### Example
```
Initial array: [5, 2, 8, 1, 9, 3]

First Pass:
[5, 2, 8, 1, 9, 3]  // Start
[2, 5, 8, 1, 9, 3]  // Swap 5 and 2
[2, 5, 1, 8, 9, 3]  // Swap 8 and 1
[2, 5, 1, 8, 3, 9]  // Swap 9 and 3

Second Pass:
[2, 1, 5, 8, 3, 9]  // Swap 5 and 1
[2, 1, 5, 3, 8, 9]  // Swap 8 and 3

Third Pass:
[1, 2, 5, 3, 8, 9]  // Swap 2 and 1
[1, 2, 3, 5, 8, 9]  // Swap 5 and 3
```

### Characteristics
1. **Time Complexity**:
   - Worst case: O(n²)
   - Best case: O(n) when array is already sorted
   - Average case: O(n²)

2. **Space Complexity**: O(1) - in-place algorithm

3. **Stability**: Stable sort (maintains relative order of equal elements)

4. **Advantages**:
   - Simple to understand and implement
   - Works well for small arrays
   - Good for nearly sorted arrays
   - No extra memory required

5. **Disadvantages**:
   - Inefficient for large arrays
   - Many swaps required
   - Not suitable for real-world applications with large datasets

### Use Cases
- Educational purposes
- Small arrays
- Nearly sorted arrays
- Situations where simplicity is more important than performance
- Demonstrating sorting concepts
- Testing and debugging other sorting algorithms