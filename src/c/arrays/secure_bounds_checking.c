#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

// Error codes
typedef enum {
    SUCCESS = 0,
    ERROR_NULL_POINTER = -1,
    ERROR_INVALID_INDEX = -2,
    ERROR_BUFFER_OVERFLOW = -3,
    ERROR_MEMORY_ALLOCATION = -4,
    ERROR_INTEGER_OVERFLOW = -5,
    ERROR_INVALID_ARRAY = -6,
    ERROR_EMPTY_ARRAY = -7,
    ERROR_FULL_ARRAY = -8
} ErrorCode;

// Secure array structure
typedef struct {
    int* data;
    size_t size;
    size_t capacity;
    bool is_valid;
} SecureArray;

// Helper function to check for integer overflow in size calculations
static bool check_size_overflow(size_t a, size_t b) {
    return a > SIZE_MAX - b;
}

// Create a new secure array
SecureArray* create_secure_array(size_t initial_capacity) {
    if (initial_capacity == 0) {
        return NULL;
    }

    SecureArray* arr = (SecureArray*)malloc(sizeof(SecureArray));
    if (!arr) {
        return NULL;
    }

    arr->data = (int*)malloc(initial_capacity * sizeof(int));
    if (!arr->data) {
        free(arr);
        return NULL;
    }

    arr->size = 0;
    arr->capacity = initial_capacity;
    arr->is_valid = true;
    return arr;
}

// Destroy a secure array
void destroy_secure_array(SecureArray* arr) {
    if (!arr) {
        return;
    }

    if (arr->is_valid) {
        free(arr->data);
        arr->data = NULL;
        arr->is_valid = false;
    }
    free(arr);
}

// Clone a secure array
SecureArray* clone_secure_array(const SecureArray* arr) {
    if (!arr || !arr->is_valid) {
        return NULL;
    }

    SecureArray* clone = create_secure_array(arr->capacity);
    if (!clone) {
        return NULL;
    }

    memcpy(clone->data, arr->data, arr->size * sizeof(int));
    clone->size = arr->size;
    return clone;
}

// Get an element from the array
int get_element(const SecureArray* arr, size_t index, int* value) {
    if (!arr || !arr->is_valid || !value) {
        return ERROR_NULL_POINTER;
    }

    if (index >= arr->size) {
        return ERROR_INVALID_INDEX;
    }

    *value = arr->data[index];
    return SUCCESS;
}

// Set an element in the array
int set_element(SecureArray* arr, size_t index, int value) {
    if (!arr || !arr->is_valid) {
        return ERROR_NULL_POINTER;
    }

    if (index >= arr->capacity) {
        return ERROR_BUFFER_OVERFLOW;
    }

    arr->data[index] = value;
    if (index >= arr->size) {
        arr->size = index + 1;
    }
    return SUCCESS;
}

// Copy one array to another
int copy_array(SecureArray* dest, const SecureArray* src) {
    if (!dest || !src || !dest->is_valid || !src->is_valid) {
        return ERROR_NULL_POINTER;
    }

    if (dest->capacity < src->size) {
        return ERROR_BUFFER_OVERFLOW;
    }

    memcpy(dest->data, src->data, src->size * sizeof(int));
    dest->size = src->size;
    return SUCCESS;
}

// Concatenate two arrays
int concatenate_arrays(SecureArray* dest, const SecureArray* src) {
    if (!dest || !src || !dest->is_valid || !src->is_valid) {
        return ERROR_NULL_POINTER;
    }

    if (check_size_overflow(dest->size, src->size)) {
        return ERROR_INTEGER_OVERFLOW;
    }

    if (dest->capacity < dest->size + src->size) {
        return ERROR_BUFFER_OVERFLOW;
    }

    memcpy(dest->data + dest->size, src->data, src->size * sizeof(int));
    dest->size += src->size;
    return SUCCESS;
}

// Slice an array
int slice_array(SecureArray* dest, const SecureArray* src, size_t start, size_t end) {
    if (!dest || !src || !dest->is_valid || !src->is_valid) {
        return ERROR_NULL_POINTER;
    }

    if (start >= src->size || end > src->size || start >= end) {
        return ERROR_INVALID_INDEX;
    }

    size_t slice_size = end - start;
    if (dest->capacity < slice_size) {
        return ERROR_BUFFER_OVERFLOW;
    }

    memcpy(dest->data, src->data + start, slice_size * sizeof(int));
    dest->size = slice_size;
    return SUCCESS;
}

// Print array contents
void print_array(const SecureArray* arr) {
    if (!arr || !arr->is_valid) {
        printf("Invalid array\n");
        return;
    }

    printf("Array[%zu/%zu]: ", arr->size, arr->capacity);
    for (size_t i = 0; i < arr->size; i++) {
        printf("%d ", arr->data[i]);
    }
    printf("\n");
}

// Test function
void test_secure_array(void) {
    printf("Testing Secure Array Operations:\n");
    printf("------------------------------\n");

    // Create arrays
    SecureArray* arr1 = create_secure_array(5);
    SecureArray* arr2 = create_secure_array(3);
    if (!arr1 || !arr2) {
        printf("Failed to create arrays\n");
        return;
    }

    // Test set_element
    printf("\n1. Setting elements:\n");
    for (int i = 0; i < 5; i++) {
        int result = set_element(arr1, i, i + 1);
        printf("Set element %d: %s\n", i + 1, 
               result == SUCCESS ? "Success" : "Failed");
    }

    // Test get_element
    printf("\n2. Getting elements:\n");
    for (int i = 0; i < 5; i++) {
        int value;
        int result = get_element(arr1, i, &value);
        printf("Get element %d: %s (value: %d)\n", i,
               result == SUCCESS ? "Success" : "Failed",
               result == SUCCESS ? value : 0);
    }

    // Test copy_array
    printf("\n3. Copying array:\n");
    int result = copy_array(arr2, arr1);
    printf("Copy array: %s\n", result == SUCCESS ? "Success" : "Failed");
    printf("Destination array after copy: ");
    print_array(arr2);

    // Test concatenate_arrays
    printf("\n4. Concatenating arrays:\n");
    result = concatenate_arrays(arr1, arr2);
    printf("Concatenate arrays: %s\n", result == SUCCESS ? "Success" : "Failed");
    printf("Result after concatenation: ");
    print_array(arr1);

    // Test slice_array
    printf("\n5. Slicing array:\n");
    SecureArray* slice = create_secure_array(3);
    if (slice) {
        result = slice_array(slice, arr1, 2, 5);
        printf("Slice array: %s\n", result == SUCCESS ? "Success" : "Failed");
        printf("Slice result: ");
        print_array(slice);
        destroy_secure_array(slice);
    }

    // Test error cases
    printf("\n6. Testing error cases:\n");
    printf("Invalid index: %d\n", get_element(arr1, 10, NULL));
    printf("NULL pointer: %d\n", set_element(NULL, 0, 1));
    printf("Buffer overflow: %d\n", set_element(arr1, 10, 1));

    // Cleanup
    destroy_secure_array(arr1);
    destroy_secure_array(arr2);
}

int main(void) {
    test_secure_array();
    return 0;
} 