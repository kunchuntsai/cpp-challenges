#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function pointer type definitions
typedef void (*Operation)(int);
typedef int (*Comparator)(const void*, const void*);
typedef void (*StringProcessor)(char*);

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

// String processing functions
void to_uppercase(char* str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - 'a' + 'A';
        }
    }
}

void to_lowercase(char* str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] - 'A' + 'a';
        }
    }
}

// Structure to demonstrate memory layout
struct MemoryLayout {
    char c;     // 1 byte
    int i;      // 4 bytes
    double d;   // 8 bytes
    char str[4]; // 4 bytes
};

// Structure to demonstrate bit fields
struct BitFields {
    unsigned int a : 3;  // 3 bits
    unsigned int b : 5;  // 5 bits
    unsigned int c : 4;  // 4 bits
};

void demonstrate_stack_vs_heap() {
    printf("\nStack vs Heap Memory:\n");
    printf("--------------------\n");

    // Stack allocation
    int stack_var = 42;
    printf("Stack variable: %d (address: %p)\n", stack_var, (void*)&stack_var);

    // Heap allocation
    int* heap_var = (int*)malloc(sizeof(int));
    if (heap_var == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    *heap_var = 42;
    printf("Heap variable: %d (address: %p)\n", *heap_var, (void*)heap_var);
    
    // Demonstrate memory leak (intentionally)
    int* leak = (int*)malloc(sizeof(int));
    *leak = 100;
    printf("Leaked memory at: %p\n", (void*)leak);
    // Note: We're not freeing 'leak' to demonstrate a memory leak
    
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
    printf("Member addresses and sizes:\n");
    printf("  char c:     %p (size: %zu)\n", (void*)&layout.c, sizeof(layout.c));
    printf("  int i:      %p (size: %zu)\n", (void*)&layout.i, sizeof(layout.i));
    printf("  double d:   %p (size: %zu)\n", (void*)&layout.d, sizeof(layout.d));
    printf("  char str[]: %p (size: %zu)\n", (void*)&layout.str, sizeof(layout.str));

    // Demonstrate bit fields
    struct BitFields bits = {7, 31, 15};  // Maximum values for each field
    printf("\nBit Fields Example:\n");
    printf("Size of BitFields: %zu bytes\n", sizeof(struct BitFields));
    printf("Values: a=%u, b=%u, c=%u\n", bits.a, bits.b, bits.c);
}

void demonstrate_endianness() {
    printf("\nEndianness Check:\n");
    printf("----------------\n");
    
    uint32_t num = 0x12345678;
    uint8_t* bytes = (uint8_t*)&num;
    
    printf("Number: 0x%x\n", num);
    printf("Bytes in memory: ");
    for (int i = 0; i < 4; i++) {
        printf("%02x ", bytes[i]);
    }
    printf("\n");
    
    if (bytes[0] == 0x78) {
        printf("System is little-endian\n");
    } else {
        printf("System is big-endian\n");
    }
}

void demonstrate_function_pointers() {
    printf("\nFunction Pointers and Callbacks:\n");
    printf("------------------------------\n");
    
    // Basic function pointer usage
    perform_operation(5, increment);
    perform_operation(5, decrement);
    
    // String processing with function pointers
    char str[] = "Hello, World!";
    StringProcessor processors[] = {to_uppercase, to_lowercase};
    
    printf("\nOriginal string: %s\n", str);
    
    processors[0](str);
    printf("After uppercase: %s\n", str);
    
    processors[1](str);
    printf("After lowercase: %s\n", str);
}

int main() {
    printf("Low-Level System Concepts\n");
    printf("=======================\n");

    // Demonstrate function pointers and callbacks
    demonstrate_function_pointers();

    // Demonstrate stack vs heap
    demonstrate_stack_vs_heap();

    // Demonstrate memory layout
    demonstrate_memory_layout();
    
    // Demonstrate endianness
    demonstrate_endianness();

    return 0;
} 