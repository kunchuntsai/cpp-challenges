#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to demonstrate memory leak
void memory_leak_demo() {
    printf("\n=== Memory Leak Demo ===\n");
    int* ptr = (int*)malloc(sizeof(int));
    *ptr = 42;
    printf("Allocated memory and stored value: %d\n", *ptr);
    // Memory leak: forgot to free the memory
    // free(ptr);  // This line is intentionally commented out
}

// Function to demonstrate dangling pointer
void dangling_pointer_demo() {
    printf("\n=== Dangling Pointer Demo ===\n");
    int* ptr = (int*)malloc(sizeof(int));
    *ptr = 100;
    printf("Before free: %d\n", *ptr);
    free(ptr);
    // Dangling pointer: accessing memory after it's freed
    printf("After free (undefined behavior): %d\n", *ptr);
}

// Function to demonstrate buffer overflow
void buffer_overflow_demo() {
    printf("\n=== Buffer Overflow Demo ===\n");
    char buffer[5];
    // Using strncpy to prevent buffer overflow
    strncpy(buffer, "Hello World", sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';  // Ensure null termination
    printf("Buffer content: %s\n", buffer);
}

// Function to demonstrate pointer arithmetic
void pointer_arithmetic_demo() {
    printf("\n=== Pointer Arithmetic Demo ===\n");
    int arr[] = {1, 2, 3, 4, 5};
    int* ptr = arr;
    
    printf("Array elements using pointer arithmetic:\n");
    for (int i = 0; i < 5; i++) {
        printf("arr[%d] = %d (address: %p)\n", i, *(ptr + i), (void*)(ptr + i));
    }
}

// Function to demonstrate multi-level pointers
void multi_level_pointer_demo() {
    printf("\n=== Multi-level Pointer Demo ===\n");
    int value = 42;
    int* ptr1 = &value;
    int** ptr2 = &ptr1;
    int*** ptr3 = &ptr2;
    
    printf("Value: %d\n", value);
    printf("Value through ptr1: %d\n", *ptr1);
    printf("Value through ptr2: %d\n", **ptr2);
    printf("Value through ptr3: %d\n", ***ptr3);
}

// Function to demonstrate proper memory management
void proper_memory_management_demo() {
    printf("\n=== Proper Memory Management Demo ===\n");
    
    // Allocate memory for an array of integers
    int* arr = (int*)malloc(5 * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    
    // Initialize array
    for (int i = 0; i < 5; i++) {
        arr[i] = i + 1;
    }
    
    // Print array
    printf("Array elements: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    // Reallocate memory to resize array
    int* new_arr = (int*)realloc(arr, 10 * sizeof(int));
    if (new_arr == NULL) {
        printf("Memory reallocation failed!\n");
        free(arr);  // Free original array if realloc fails
        return;
    }
    arr = new_arr;
    
    // Initialize new elements
    for (int i = 5; i < 10; i++) {
        arr[i] = i + 1;
    }
    
    // Print resized array
    printf("Resized array elements: ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    // Free memory
    free(arr);
    printf("Memory properly freed\n");
}

int main() {
    printf("Pointer Manipulation & Memory Management Examples\n");
    printf("==============================================\n");
    
    // Run demos
    proper_memory_management_demo();
    pointer_arithmetic_demo();
    multi_level_pointer_demo();
    
    // Uncomment these to see problematic behavior
    // memory_leak_demo();
    // dangling_pointer_demo();
    // buffer_overflow_demo();
    
    return 0;
} 