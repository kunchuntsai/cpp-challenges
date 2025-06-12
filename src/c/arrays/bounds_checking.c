/*
 * CODING INTERVIEW QUESTION: Safe Array Operations with Bounds Checking
 *
 * Problem: Implement a safe string copy function that prevents buffer overflows.
 * Write a function that copies from source to destination with proper bounds checking.
 *
 * Requirements:
 * 1. Function should never write beyond the destination buffer size
 * 2. Always null-terminate the destination string
 * 3. Return the number of characters copied (excluding null terminator)
 * 4. Handle edge cases: NULL pointers, zero-size buffers
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// QUESTION: Implement this function
int safe_strcpy(char *dest, const char *src, size_t dest_size) {
    // Check for NULL pointers or zero size
    if (dest == NULL || src == NULL || dest_size == 0) {
        return -1;
    }

    size_t i;
    // Copy characters up to dest_size - 1 (leaving room for null terminator)
    for (i = 0; i < dest_size - 1 && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }

    // Always null-terminate
    dest[i] = '\0';

    // Return number of characters copied (excluding null terminator)
    return i;
}

// BONUS QUESTION: Implement safe array concatenation
int safe_strcat(char *dest, const char *src, size_t dest_size) {
    // Check for NULL pointers or zero size
    if (dest == NULL || src == NULL || dest_size == 0) {
        return -1;
    }

    // Find end of destination string
    size_t dest_len = strlen(dest);
    if (dest_len >= dest_size) {
        return -1;  // Destination string is already full
    }

    size_t i;
    // Append characters up to remaining space
    for (i = 0; i < dest_size - dest_len - 1 && src[i] != '\0'; i++) {
        dest[dest_len + i] = src[i];
    }

    // Always null-terminate
    dest[dest_len + i] = '\0';

    // Return number of characters appended (excluding null terminator)
    return i;
}

// Test cases to verify your implementation
int main() {
    char buffer[10];
    char small_buffer[5];

    // Test Case 1: Normal operation
    printf("Test 1 - Normal copy:\n");
    int copied = safe_strcpy(buffer, "Hello", sizeof(buffer));
    printf("Copied: %d chars, Result: '%s'\n", copied, buffer);

    // Test Case 2: Buffer too small (should truncate safely)
    printf("\nTest 2 - Buffer overflow prevention:\n");
    copied = safe_strcpy(small_buffer, "This is too long", sizeof(small_buffer));
    printf("Copied: %d chars, Result: '%s'\n", copied, small_buffer);

    // Test Case 3: Edge case - empty string
    printf("\nTest 3 - Empty string:\n");
    copied = safe_strcpy(buffer, "", sizeof(buffer));
    printf("Copied: %d chars, Result: '%s'\n", copied, buffer);

    // Test Case 4: NULL pointer handling
    printf("\nTest 4 - NULL pointer:\n");
    copied = safe_strcpy(NULL, "test", 10);
    printf("Copied: %d chars (should be -1 for error)\n", copied);

    return 0;
}

/*
 * EXPECTED BEHAVIOR:
 * - Test 1: Should copy "Hello" completely (5 chars)
 * - Test 2: Should copy "This" only (4 chars) and null-terminate
 * - Test 3: Should copy empty string (0 chars)
 * - Test 4: Should return -1 for error
 *
 * COMMON MISTAKES TO AVOID:
 * 1. Not checking if dest_size is 0
 * 2. Forgetting to null-terminate
 * 3. Not handling NULL pointers
 * 4. Off-by-one errors in buffer size calculation
 * 5. Not returning correct count of copied characters
 */