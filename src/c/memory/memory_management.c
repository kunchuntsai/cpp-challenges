#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

// Memory block header structure
typedef struct MemoryBlock {
    size_t size;           // Size of the allocated block
    bool is_free;          // Whether the block is free
    struct MemoryBlock* next;  // Next block in the list
} MemoryBlock;

// Global variables for memory management
static MemoryBlock* memory_head = NULL;
static const size_t MIN_BLOCK_SIZE = sizeof(MemoryBlock);
static const size_t HEAP_SIZE = 1024 * 1024;  // 1MB heap size
static uint8_t heap[HEAP_SIZE];  // Static heap

// Initialize the memory system
void init_memory_system(void) {
    memory_head = (MemoryBlock*)heap;
    memory_head->size = HEAP_SIZE - MIN_BLOCK_SIZE;
    memory_head->is_free = true;
    memory_head->next = NULL;
}

// Custom malloc implementation
void* custom_malloc(size_t size) {
    if (size == 0) return NULL;

    // Add header size to requested size
    size_t total_size = size + MIN_BLOCK_SIZE;

    // Find a suitable free block
    MemoryBlock* current = memory_head;
    while (current != NULL) {
        if (current->is_free && current->size >= total_size) {
            // Split block if it's large enough
            if (current->size >= total_size + MIN_BLOCK_SIZE + 16) {
                MemoryBlock* new_block = (MemoryBlock*)((uint8_t*)current + total_size);
                new_block->size = current->size - total_size;
                new_block->is_free = true;
                new_block->next = current->next;

                current->size = total_size;
                current->next = new_block;
            }

            current->is_free = false;
            return (void*)((uint8_t*)current + MIN_BLOCK_SIZE);
        }
        current = current->next;
    }

    return NULL;  // No suitable block found
}

// Custom free implementation
void custom_free(void* ptr) {
    if (ptr == NULL) return;

    // Get the block header
    MemoryBlock* block = (MemoryBlock*)((uint8_t*)ptr - MIN_BLOCK_SIZE);
    block->is_free = true;

    // Coalesce adjacent free blocks
    MemoryBlock* current = memory_head;
    while (current != NULL && current->next != NULL) {
        if (current->is_free && current->next->is_free) {
            current->size += current->next->size + MIN_BLOCK_SIZE;
            current->next = current->next->next;
        } else {
            current = current->next;
        }
    }
}

// Safe string copy functions
size_t safe_strcpy(char* dest, const char* src, size_t dest_size) {
    if (dest == NULL || src == NULL || dest_size == 0) {
        return 0;
    }

    size_t i;
    for (i = 0; i < dest_size - 1 && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';

    return i;
}

size_t safe_strncpy(char* dest, const char* src, size_t dest_size, size_t n) {
    if (dest == NULL || src == NULL || dest_size == 0) {
        return 0;
    }

    size_t i;
    for (i = 0; i < dest_size - 1 && i < n && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';

    return i;
}

// Test function
void test_memory_management(void) {
    printf("Testing Custom Memory Management\n");
    printf("==============================\n");

    // Initialize memory system
    init_memory_system();

    // Test malloc
    char* str1 = (char*)custom_malloc(50);
    if (str1) {
        safe_strcpy(str1, "Hello, World!", 50);
        printf("Allocated string: %s\n", str1);
    }

    // Test multiple allocations
    int* numbers = (int*)custom_malloc(5 * sizeof(int));
    if (numbers) {
        for (int i = 0; i < 5; i++) {
            numbers[i] = i + 1;
        }
        printf("Allocated numbers: ");
        for (int i = 0; i < 5; i++) {
            printf("%d ", numbers[i]);
        }
        printf("\n");
    }

    // Test free
    custom_free(str1);
    custom_free(numbers);

    // Test safe string copy
    char dest[20];
    const char* src = "This is a test string";

    size_t copied = safe_strcpy(dest, src, sizeof(dest));
    printf("Safe string copy result: %s (copied %zu characters)\n", dest, copied);

    // Test safe string copy with truncation
    char dest2[10];
    copied = safe_strcpy(dest2, src, sizeof(dest2));
    printf("Safe string copy with truncation: %s (copied %zu characters)\n", dest2, copied);

    // Test safe strncpy
    char dest3[15];
    copied = safe_strncpy(dest3, src, sizeof(dest3), 5);
    printf("Safe strncpy result: %s (copied %zu characters)\n", dest3, copied);
}

int main(void) {
    test_memory_management();
    return 0;
}