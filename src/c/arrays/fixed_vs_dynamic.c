#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define FIXED_ARRAY_SIZE 10
#define INITIAL_DYNAMIC_CAPACITY 5

// Structure to represent a dynamic array
typedef struct {
    int* data;
    size_t size;
    size_t capacity;
} DynamicArray;

// Fixed array operations
void init_fixed_array(int arr[], size_t size) {
    for (size_t i = 0; i < size; i++) {
        arr[i] = 0;
    }
}

int add_to_fixed_array(int arr[], size_t size, size_t* current_size, int value) {
    if (*current_size >= size) {
        return 0; // Array is full
    }
    arr[*current_size] = value;
    (*current_size)++;
    return 1;
}

int remove_from_fixed_array(int arr[], size_t* current_size) {
    if (*current_size == 0) {
        return 0; // Array is empty
    }
    // Zero out the last element before removing it
    arr[*current_size - 1] = 0;
    (*current_size)--;
    return 1;
}

void print_fixed_array(const int arr[], size_t size) {
    printf("Fixed Array: [");
    for (size_t i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]\n");
}

// Dynamic array operations
DynamicArray* create_dynamic_array(void) {
    DynamicArray* da = malloc(sizeof(DynamicArray));
    if (!da) return NULL;

    da->data = malloc(INITIAL_DYNAMIC_CAPACITY * sizeof(int));
    if (!da->data) {
        free(da);
        return NULL;
    }

    da->size = 0;
    da->capacity = INITIAL_DYNAMIC_CAPACITY;
    return da;
}

void free_dynamic_array(DynamicArray* da) {
    if (da) {
        free(da->data);
        free(da);
    }
}

int resize_dynamic_array(DynamicArray* da) {
    size_t new_capacity = da->capacity * 2;
    int* new_data = realloc(da->data, new_capacity * sizeof(int));
    if (!new_data) return 0;

    da->data = new_data;
    da->capacity = new_capacity;
    return 1;
}

int add_to_dynamic_array(DynamicArray* da, int value) {
    if (da->size >= da->capacity) {
        if (!resize_dynamic_array(da)) {
            return 0; // Resize failed
        }
    }
    da->data[da->size] = value;
    da->size++;
    return 1;
}

int remove_from_dynamic_array(DynamicArray* da) {
    if (da->size == 0) {
        return 0; // Array is empty
    }
    da->size--;
    return 1;
}

void print_dynamic_array(const DynamicArray* da) {
    printf("Dynamic Array: [");
    for (size_t i = 0; i < da->size; i++) {
        printf("%d", da->data[i]);
        if (i < da->size - 1) printf(", ");
    }
    printf("] (capacity: %zu)\n", da->capacity);
}

// Example usage
void demonstrate_fixed_array(void) {
    printf("\n=== Fixed Array Demonstration ===\n");
    int fixed_arr[FIXED_ARRAY_SIZE];
    size_t current_size = 0;

    init_fixed_array(fixed_arr, FIXED_ARRAY_SIZE);
    print_fixed_array(fixed_arr, current_size);

    // Add elements
    for (int i = 1; i <= 12; i++) {
        if (add_to_fixed_array(fixed_arr, FIXED_ARRAY_SIZE, &current_size, i)) {
            printf("Added %d: ", i);
            print_fixed_array(fixed_arr, current_size);
        } else {
            printf("Failed to add %d - array is full\n", i);
        }
    }

    // Remove elements
    for (int i = 0; i < 3; i++) {
        if (remove_from_fixed_array(fixed_arr, &current_size)) {
            printf("Removed element: ");
            print_fixed_array(fixed_arr, current_size);
        }
    }
}

void demonstrate_dynamic_array(void) {
    printf("\n=== Dynamic Array Demonstration ===\n");
    DynamicArray* da = create_dynamic_array();
    if (!da) {
        printf("Failed to create dynamic array\n");
        return;
    }

    print_dynamic_array(da);

    // Add elements
    for (int i = 1; i <= 12; i++) {
        if (add_to_dynamic_array(da, i)) {
            printf("Added %d: ", i);
            print_dynamic_array(da);
        } else {
            printf("Failed to add %d\n", i);
        }
    }

    // Remove elements
    for (int i = 0; i < 3; i++) {
        if (remove_from_dynamic_array(da)) {
            printf("Removed element: ");
            print_dynamic_array(da);
        }
    }

    free_dynamic_array(da);
}

int main(void) {
    demonstrate_fixed_array();
    demonstrate_dynamic_array();
    return 0;
}