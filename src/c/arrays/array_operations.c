#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fixed-size array operations
void print_array(const int* arr, size_t size) {
    printf("Array contents: ");
    for (size_t i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void reverse_array(int* arr, size_t size) {
    for (size_t i = 0; i < size / 2; i++) {
        int temp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }
}

// Dynamic array implementation
typedef struct {
    int* data;
    size_t size;
    size_t capacity;
} DynamicArray;

DynamicArray* create_dynamic_array(size_t initial_capacity) {
    DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));
    if (!arr) return NULL;
    
    arr->data = (int*)malloc(initial_capacity * sizeof(int));
    if (!arr->data) {
        free(arr);
        return NULL;
    }
    
    arr->size = 0;
    arr->capacity = initial_capacity;
    return arr;
}

void free_dynamic_array(DynamicArray* arr) {
    if (arr) {
        free(arr->data);
        free(arr);
    }
}

int push_back(DynamicArray* arr, int value) {
    if (arr->size >= arr->capacity) {
        size_t new_capacity = arr->capacity * 2;
        int* new_data = (int*)realloc(arr->data, new_capacity * sizeof(int));
        if (!new_data) return 0;
        
        arr->data = new_data;
        arr->capacity = new_capacity;
    }
    
    arr->data[arr->size++] = value;
    return 1;
}

// Circular buffer implementation
typedef struct {
    int* buffer;
    size_t capacity;
    size_t head;
    size_t tail;
    size_t size;
} CircularBuffer;

CircularBuffer* create_circular_buffer(size_t capacity) {
    CircularBuffer* cb = (CircularBuffer*)malloc(sizeof(CircularBuffer));
    if (!cb) return NULL;
    
    cb->buffer = (int*)malloc(capacity * sizeof(int));
    if (!cb->buffer) {
        free(cb);
        return NULL;
    }
    
    cb->capacity = capacity;
    cb->head = 0;
    cb->tail = 0;
    cb->size = 0;
    return cb;
}

void free_circular_buffer(CircularBuffer* cb) {
    if (cb) {
        free(cb->buffer);
        free(cb);
    }
}

int circular_buffer_push(CircularBuffer* cb, int value) {
    if (cb->size >= cb->capacity) return 0;
    
    cb->buffer[cb->tail] = value;
    cb->tail = (cb->tail + 1) % cb->capacity;
    cb->size++;
    return 1;
}

int circular_buffer_pop(CircularBuffer* cb, int* value) {
    if (cb->size == 0) return 0;
    
    *value = cb->buffer[cb->head];
    cb->head = (cb->head + 1) % cb->capacity;
    cb->size--;
    return 1;
}

void print_circular_buffer(const CircularBuffer* cb) {
    printf("Circular Buffer contents: ");
    if (cb->size == 0) {
        printf("(empty)\n");
        return;
    }
    
    size_t current = cb->head;
    for (size_t i = 0; i < cb->size; i++) {
        printf("%d ", cb->buffer[current]);
        current = (current + 1) % cb->capacity;
    }
    printf("\n");
}

// Test function
void test_array_operations() {
    printf("Testing Array Operations:\n");
    printf("------------------------\n");
    
    // Test fixed-size array
    printf("\n1. Fixed-size Array Operations:\n");
    int fixed_array[] = {1, 2, 3, 4, 5};
    size_t fixed_size = sizeof(fixed_array) / sizeof(fixed_array[0]);
    
    printf("Original array: ");
    print_array(fixed_array, fixed_size);
    
    reverse_array(fixed_array, fixed_size);
    printf("Reversed array: ");
    print_array(fixed_array, fixed_size);
    
    // Test dynamic array
    printf("\n2. Dynamic Array Operations:\n");
    DynamicArray* dyn_arr = create_dynamic_array(2);
    if (!dyn_arr) {
        printf("Failed to create dynamic array\n");
        return;
    }
    
    printf("Pushing values: ");
    for (int i = 1; i <= 5; i++) {
        if (push_back(dyn_arr, i)) {
            printf("%d ", i);
        }
    }
    printf("\n");
    
    printf("Dynamic array contents: ");
    print_array(dyn_arr->data, dyn_arr->size);
    printf("Current capacity: %zu\n", dyn_arr->capacity);
    
    // Test circular buffer
    printf("\n3. Circular Buffer Operations:\n");
    CircularBuffer* cb = create_circular_buffer(4);
    if (!cb) {
        printf("Failed to create circular buffer\n");
        free_dynamic_array(dyn_arr);
        return;
    }
    
    printf("Pushing values to circular buffer: ");
    for (int i = 1; i <= 6; i++) {
        if (circular_buffer_push(cb, i)) {
            printf("%d ", i);
        } else {
            printf("(buffer full) ");
        }
    }
    printf("\n");
    
    print_circular_buffer(cb);
    
    printf("Popping values from circular buffer: ");
    int value;
    while (circular_buffer_pop(cb, &value)) {
        printf("%d ", value);
    }
    printf("\n");
    
    // Cleanup
    free_dynamic_array(dyn_arr);
    free_circular_buffer(cb);
}

int main() {
    test_array_operations();
    return 0;
} 