#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ========================================
// MEMORY MANAGEMENT ERRORS & SOLUTIONS
// ========================================

// ========================================
// ERROR 1: Basic Memory Leak
// ========================================

// BUGGY CODE:
void memory_leak_example() {
    int* ptr = (int*)malloc(sizeof(int));
    *ptr = 42;
    // Memory leak: forgot to free the memory
    // Fix: Add free(ptr);
}

// BUGGY CODE:
char* create_string_buggy(const char* input) {
    char* result = malloc(strlen(input) + 1);
    strcpy(result, input);
    return result;
    // BUG: Caller might forget to free, causing memory leak
}

void use_string_buggy() {
    char* str = create_string_buggy("Hello World");
    printf("%s\n", str);
    // BUG: Missing free(str) - MEMORY LEAK!
}

// FIXED VERSION:
char* create_string_fixed(const char* input) {
    char* result = malloc(strlen(input) + 1);
    if (result == NULL) {
        return NULL; // Handle allocation failure
    }
    strcpy(result, input);
    return result;
}

void use_string_fixed() {
    char* str = create_string_fixed("Hello World");
    if (str != NULL) {
        printf("%s\n", str);
        free(str); // FIXED: Free the memory
        str = NULL; // Good practice: avoid dangling pointer
    }
}

// ========================================
// ERROR 2: Double Free
// ========================================

// BUGGY CODE:
void double_free_example() {
    int* ptr = (int*)malloc(sizeof(int));
    *ptr = 42;
    free(ptr);
    free(ptr);  // Error: double free
    // Fix: Remove the second free(ptr)
}

// BUGGY CODE:
void double_free_bug() {
    char* ptr = malloc(100);
    strcpy(ptr, "Some data");
    
    free(ptr);
    // ... some other code ...
    free(ptr); // BUG: Double free - undefined behavior!
}

// FIXED VERSION:
void double_free_fixed() {
    char* ptr = malloc(100);
    if (ptr == NULL) return;
    
    strcpy(ptr, "Some data");
    
    free(ptr);
    ptr = NULL; // FIXED: Set pointer to NULL after freeing
    
    // Now this is safe (freeing NULL is allowed)
    if (ptr != NULL) {
        free(ptr);
    }
}

// ========================================
// ERROR 3: Use After Free (Dangling Pointer)
// ========================================

// BUGGY CODE:
void use_after_free_example() {
    int* ptr = (int*)malloc(sizeof(int));
    *ptr = 42;
    free(ptr);
    *ptr = 100;  // Error: using memory after it's freed
    // Fix: Don't use the pointer after freeing it
}

// BUGGY CODE:
void use_after_free_bug() {
    int* arr = malloc(5 * sizeof(int));
    for (int i = 0; i < 5; i++) {
        arr[i] = i * 10;
    }
    
    free(arr);
    
    // BUG: Using freed memory
    printf("First element: %d\n", arr[0]); // Undefined behavior!
}

// FIXED VERSION:
void use_after_free_fixed() {
    int* arr = malloc(5 * sizeof(int));
    if (arr == NULL) return;
    
    for (int i = 0; i < 5; i++) {
        arr[i] = i * 10;
    }
    
    // Use the data before freeing
    printf("First element: %d\n", arr[0]);
    
    free(arr);
    arr = NULL; // FIXED: Prevent accidental use
}

// ========================================
// ERROR 4: Memory Leak in Loop
// ========================================

// BUGGY CODE:
void memory_leak_in_loop() {
    for (int i = 0; i < 10; i++) {
        int* ptr = (int*)malloc(sizeof(int));
        *ptr = i;
        // Memory leak: new allocation in each iteration without freeing
    }
    // Fix: Free the memory inside the loop or store pointers in an array
}

// BUGGY CODE:
void loop_leak_bug() {
    for (int i = 0; i < 1000; i++) {
        char* buffer = malloc(1024);
        sprintf(buffer, "Iteration %d", i);
        printf("%s\n", buffer);
        // BUG: Never freed - 1000 memory leaks!
    }
}

// FIXED VERSION:
void loop_leak_fixed() {
    for (int i = 0; i < 1000; i++) {
        char* buffer = malloc(1024);
        if (buffer == NULL) {
            printf("Memory allocation failed\n");
            continue;
        }
        sprintf(buffer, "Iteration %d", i);
        printf("%s\n", buffer);
        free(buffer); // FIXED: Free in each iteration
    }
}

// ========================================
// ERROR 5: Incorrect Array Allocation
// ========================================

// BUGGY CODE:
void incorrect_array_allocation() {
    int* arr = (int*)malloc(5);  // Error: should be 5 * sizeof(int)
    // Fix: int* arr = (int*)malloc(5 * sizeof(int));
    free(arr);
}

// ========================================
// ERROR 6: Memory Leak in Error Handling
// ========================================

// BUGGY CODE:
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

// BUGGY CODE:
int process_data_buggy(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) return -1;
    
    char* buffer1 = malloc(1024);
    char* buffer2 = malloc(2048);
    
    if (buffer1 == NULL) {
        fclose(file);
        return -1; // BUG: buffer2 not freed if allocated
    }
    
    if (buffer2 == NULL) {
        fclose(file);
        return -1; // BUG: buffer1 not freed
    }
    
    // Process data...
    
    free(buffer1);
    free(buffer2);
    fclose(file);
    return 0;
}

// FIXED VERSION:
int process_data_fixed(const char* filename) {
    FILE* file = NULL;
    char* buffer1 = NULL;
    char* buffer2 = NULL;
    int result = -1;
    
    file = fopen(filename, "r");
    if (file == NULL) {
        goto cleanup;
    }
    
    buffer1 = malloc(1024);
    if (buffer1 == NULL) {
        goto cleanup;
    }
    
    buffer2 = malloc(2048);
    if (buffer2 == NULL) {
        goto cleanup;
    }
    
    // Process data...
    result = 0; // Success
    
cleanup:
    // FIXED: Centralized cleanup handles all cases
    if (buffer2) free(buffer2);
    if (buffer1) free(buffer1);
    if (file) fclose(file);
    
    return result;
}

// ========================================
// ERROR 7: String Memory Management
// ========================================

// BUGGY CODE:
void string_memory_management() {
    char* str = (char*)malloc(6);
    strcpy(str, "Hello");
    str = "World";  // Memory leak: lost reference to allocated memory
    // Fix: Either free(str) before reassignment or use strncpy
}

// BUGGY CODE:
void buffer_overflow_bug() {
    char* buffer = malloc(10);
    strcpy(buffer, "This string is way too long for the buffer"); // BUG: Overflow!
    printf("%s\n", buffer);
    free(buffer);
}

// FIXED VERSION:
void buffer_overflow_fixed() {
    const char* source = "This string is way too long for the buffer";
    size_t needed_size = strlen(source) + 1;
    
    char* buffer = malloc(needed_size); // FIXED: Allocate enough space
    if (buffer == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    
    strcpy(buffer, source); // Now safe
    printf("%s\n", buffer);
    free(buffer);
}

// Alternative fix with fixed buffer size:
void buffer_overflow_fixed_alt() {
    char* buffer = malloc(10);
    if (buffer == NULL) return;
    
    const char* source = "This string is way too long for the buffer";
    strncpy(buffer, source, 9); // FIXED: Use strncpy with size limit
    buffer[9] = '\0'; // Ensure null termination
    
    printf("%s\n", buffer);
    free(buffer);
}

// ========================================
// ERROR 8: Freeing Stack Memory
// ========================================

// BUGGY CODE:
char* get_string_buggy() {
    char local_array[100] = "Hello World";
    return local_array; // BUG: Returning pointer to stack memory
}

void use_stack_memory_bug() {
    char* str = get_string_buggy();
    printf("%s\n", str); // BUG: Accessing invalid memory
    // free(str); // BUG: Trying to free stack memory would crash
}

// FIXED VERSION:
char* get_string_fixed() {
    char* heap_string = malloc(100);
    if (heap_string == NULL) return NULL;
    
    strcpy(heap_string, "Hello World");
    return heap_string; // FIXED: Return heap memory
}

void use_stack_memory_fixed() {
    char* str = get_string_fixed();
    if (str != NULL) {
        printf("%s\n", str);
        free(str); // FIXED: Now safe to free
    }
}

// ========================================
// ERROR 9: Leaked Resources in Struct
// ========================================

typedef struct {
    char* name;
    int* data;
    size_t size;
} DataStruct;

// BUGGY CODE:
DataStruct* create_struct_buggy(const char* name, size_t size) {
    DataStruct* ds = malloc(sizeof(DataStruct));
    ds->name = malloc(strlen(name) + 1);
    strcpy(ds->name, name);
    ds->data = malloc(size * sizeof(int));
    ds->size = size;
    return ds;
    // BUG: No cleanup function provided
}

void use_struct_buggy() {
    DataStruct* ds = create_struct_buggy("test", 100);
    // ... use ds ...
    free(ds); // BUG: Only frees struct, not internal pointers!
}

// FIXED VERSION:
DataStruct* create_struct_fixed(const char* name, size_t size) {
    DataStruct* ds = malloc(sizeof(DataStruct));
    if (ds == NULL) return NULL;
    
    ds->name = malloc(strlen(name) + 1);
    if (ds->name == NULL) {
        free(ds);
        return NULL;
    }
    
    ds->data = malloc(size * sizeof(int));
    if (ds->data == NULL) {
        free(ds->name);
        free(ds);
        return NULL;
    }
    
    strcpy(ds->name, name);
    ds->size = size;
    return ds;
}

void destroy_struct_fixed(DataStruct* ds) {
    if (ds != NULL) {
        free(ds->name);   // FIXED: Free internal memory first
        free(ds->data);   // FIXED: Free internal memory first
        free(ds);         // Then free the struct itself
    }
}

void use_struct_fixed() {
    DataStruct* ds = create_struct_fixed("test", 100);
    if (ds != NULL) {
        // ... use ds ...
        destroy_struct_fixed(ds); // FIXED: Proper cleanup
    }
}

// ========================================
// DEBUGGING TIPS AND TOOLS
// ========================================

/*
DEBUGGING MEMORY ISSUES:

1. Use Valgrind (Linux/Mac):
   valgrind --leak-check=full ./your_program

2. Use AddressSanitizer (GCC/Clang):
   gcc -fsanitize=address -g program.c

3. Static Analysis:
   - Clang Static Analyzer
   - Cppcheck
   - PC-lint

4. Good Practices:
   - Always check malloc return value
   - Set pointers to NULL after freeing
   - Use consistent allocation/deallocation patterns
   - Initialize pointers to NULL
   - Free in reverse order of allocation for complex structures

5. Memory Debugging Patterns:
   - RAII-like patterns in C (init/cleanup pairs)
   - Use goto for centralized cleanup
   - Wrapper functions for allocation/deallocation
*/

// Example of a safe string duplication function
char* safe_strdup(const char* src) {
    if (src == NULL) return NULL;
    
    size_t len = strlen(src) + 1;
    char* dst = malloc(len);
    if (dst == NULL) return NULL;
    
    memcpy(dst, src, len);
    return dst;
}

int main() {
    printf("Memory Management Examples:\n");
    printf("Run with Valgrind or AddressSanitizer to detect issues\n");
    
    // Test the fixed versions
    use_string_fixed();
    double_free_fixed();
    use_after_free_fixed();
    loop_leak_fixed();
    buffer_overflow_fixed();
    use_stack_memory_fixed();
    
    // Test struct management
    DataStruct* ds = create_struct_fixed("test", 100);
    if (ds != NULL) {
        destroy_struct_fixed(ds);
    }
    
    return 0;
} 