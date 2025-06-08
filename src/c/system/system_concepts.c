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

// Comparison function for integers
int compare_ints(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
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

    printf("\nMemory Layout Analysis:\n");
    printf("=====================\n\n");

    // Print structure boundaries
    printf("1. Structure Overview:\n");
    printf("   -----------------\n");
    printf("   Start address:  %p\n", (void*)&layout);
    printf("   End address:    %p\n", (void*)((char*)&layout + sizeof(struct MemoryLayout)));
    printf("   Total size:     %zu bytes\n\n", sizeof(struct MemoryLayout));

    // Verify alignment
    printf("2. Member Alignment:\n");
    printf("   ---------------\n");
    printf("   char c:     %p (1 byte)\n", (void*)&layout.c);
    printf("   int i:      %p (4 bytes, offset: %zu)\n",
           (void*)&layout.i, (size_t)&layout.i - (size_t)&layout);
    printf("   double d:   %p (8 bytes, offset: %zu)\n",
           (void*)&layout.d, (size_t)&layout.d - (size_t)&layout);
    printf("   char str[]: %p (4 bytes, offset: %zu)\n\n",
           (void*)&layout.str, (size_t)&layout.str - (size_t)&layout);

    // Print complete memory layout with addresses
    printf("3. Detailed Memory Layout:\n");
    printf("   ---------------------\n");

    // Calculate and print each byte's address
    unsigned char* base = (unsigned char*)&layout;

    printf("   [0x%p] char c:      ", (void*)base);
    for(size_t i = 0; i < sizeof(layout.c); i++) {
        printf("%02x ", *(base + i));
    }
    printf("\n");

    printf("   [0x%p] padding 1:   ", (void*)(base + sizeof(layout.c)));
    for(size_t i = sizeof(layout.c); i < (size_t)&layout.i - (size_t)&layout.c; i++) {
        printf("%02x ", *(base + i));
    }
    printf("\n");

    printf("   [0x%p] int i:       ", (void*)&layout.i);
    for(size_t i = (size_t)&layout.i - (size_t)&layout.c;
        i < (size_t)&layout.i - (size_t)&layout.c + sizeof(layout.i); i++) {
        printf("%02x ", *(base + i));
    }
    printf("\n");

    printf("   [0x%p] double d:    ", (void*)&layout.d);
    for(size_t i = (size_t)&layout.d - (size_t)&layout.c;
        i < (size_t)&layout.d - (size_t)&layout.c + sizeof(layout.d); i++) {
        printf("%02x ", *(base + i));
    }
    printf("\n");

    printf("   [0x%p] char str[]:  ", (void*)&layout.str);
    for(size_t i = (size_t)&layout.str - (size_t)&layout.c;
        i < (size_t)&layout.str - (size_t)&layout.c + sizeof(layout.str); i++) {
        printf("%02x ", *(base + i));
    }
    printf("\n");

    printf("   [0x%p] end padding: ",
           (void*)(base + (size_t)&layout.str - (size_t)&layout.c + sizeof(layout.str)));
    for(size_t i = (size_t)&layout.str - (size_t)&layout.c + sizeof(layout.str);
        i < sizeof(struct MemoryLayout); i++) {
        printf("%02x ", *(base + i));
    }
    printf("\n\n");

    // Calculate end padding
    size_t end_padding = sizeof(struct MemoryLayout) -
                        ((size_t)&layout.str - (size_t)&layout.c + sizeof(layout.str));

    // Verify total size matches our calculations
    size_t calculated_size = (size_t)&layout.str - (size_t)&layout.c + sizeof(layout.str) + end_padding;

    printf("4. Size Verification:\n");
    printf("   -----------------\n");
    printf("   Actual size:    %zu bytes\n", sizeof(struct MemoryLayout));
    printf("   Calculated:     %zu bytes\n", calculated_size);
    printf("   Padding total:  %zu bytes\n",
           sizeof(struct MemoryLayout) - (sizeof(layout.c) + sizeof(layout.i) +
           sizeof(layout.d) + sizeof(layout.str)));
    printf("   Verification:   %s\n",
           sizeof(struct MemoryLayout) == calculated_size ? "✓ PASS" : "✗ FAIL");

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

// Simple bubble sort using function pointer
void bubble_sort(int arr[], int size, Comparator compare) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            // Use the comparison function pointer
            if (compare(&arr[j], &arr[j + 1]) > 0) {
                // Swap elements
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
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

    // Demonstrate Comparator usage with qsort
    printf("\nComparator Example with qsort:\n");
    printf("----------------------------\n");

    int numbers[] = {5, 2, 8, 1, 9, 3};
    int num_count = sizeof(numbers) / sizeof(numbers[0]);

    printf("Original array: ");
    for (int i = 0; i < num_count; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    // Use qsort with our comparison function
    qsort(numbers, num_count, sizeof(int), compare_ints);

    printf("Sorted array (qsort):   ");
    for (int i = 0; i < num_count; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    // Demonstrate Comparator usage with our bubble sort
    printf("\nComparator Example with bubble sort:\n");
    printf("----------------------------------\n");

    int numbers2[] = {5, 2, 8, 1, 9, 3};  // New array with same values

    printf("Original array: ");
    for (int i = 0; i < num_count; i++) {
        printf("%d ", numbers2[i]);
    }
    printf("\n");

    // Use bubble_sort with our comparison function
    bubble_sort(numbers2, num_count, compare_ints);

    printf("Sorted array (bubble):   ");
    for (int i = 0; i < num_count; i++) {
        printf("%d ", numbers2[i]);
    }
    printf("\n");
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