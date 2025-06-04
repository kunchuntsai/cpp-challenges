#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function pointer type definition
typedef void (*Operation)(int);

// Example callback functions
void increment(int x) {
    printf("Incrementing %d to %d\n", x, x + 1);
}

void decrement(int x) {
    printf("Decrementing %d to %d\n", x, x - 1);
}

// Function that takes a callback
void perform_operation(int value, Operation op) {
    printf("Performing operation on value: %d\n", value);
    op(value);
}

// Structure to demonstrate memory layout
struct MemoryLayout {
    char c;     // 1 byte
    int i;      // 4 bytes
    double d;   // 8 bytes
    char str[4]; // 4 bytes
};

void demonstrate_stack_vs_heap() {
    printf("\nStack vs Heap Memory:\n");
    printf("--------------------\n");

    // Stack allocation
    int stack_var = 42;
    printf("Stack variable: %d (address: %p)\n", stack_var, (void*)&stack_var);

    // Heap allocation
    int* heap_var = (int*)malloc(sizeof(int));
    *heap_var = 42;
    printf("Heap variable: %d (address: %p)\n", *heap_var, (void*)heap_var);
    
    // Don't forget to free heap memory
    free(heap_var);
}

void demonstrate_memory_layout() {
    printf("\nMemory Layout Example:\n");
    printf("---------------------\n");

    struct MemoryLayout layout = {
        .c = 'A',
        .i = 42,
        .d = 3.14,
        .str = "ABC"
    };

    printf("Structure size: %zu bytes\n", sizeof(struct MemoryLayout));
    printf("Member addresses:\n");
    printf("  char c:     %p\n", (void*)&layout.c);
    printf("  int i:      %p\n", (void*)&layout.i);
    printf("  double d:   %p\n", (void*)&layout.d);
    printf("  char str[]: %p\n", (void*)&layout.str);
}

int main() {
    printf("Low-Level System Concepts\n");
    printf("=======================\n");

    // Demonstrate function pointers and callbacks
    printf("\nFunction Pointers and Callbacks:\n");
    printf("------------------------------\n");
    perform_operation(5, increment);
    perform_operation(5, decrement);

    // Demonstrate stack vs heap
    demonstrate_stack_vs_heap();

    // Demonstrate memory layout
    demonstrate_memory_layout();

    return 0;
} 