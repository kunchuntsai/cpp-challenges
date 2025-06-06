# Safe Array Operations with Bounds Checking

## Problem Description
Implement safe string operations that prevent buffer overflows. The problem consists of two parts:
1. A safe string copy function
2. A safe string concatenation function

Both functions must ensure that operations never write beyond the destination buffer size and properly handle edge cases.

### Requirements
1. Functions should never write beyond the destination buffer size
2. Always null-terminate the destination string
3. Return the number of characters copied/appended (excluding null terminator)
4. Handle edge cases: NULL pointers, zero-size buffers

## Solution Approach

### Safe String Copy (`safe_strcpy`)
The implementation ensures safe copying by:
1. Validating input parameters (NULL checks and size validation)
2. Copying characters up to dest_size - 1 (leaving room for null terminator)
3. Always null-terminating the destination string
4. Returning the number of characters copied

### Safe String Concatenation (`safe_strcat`)
The implementation ensures safe concatenation by:
1. Validating input parameters
2. Finding the end of the destination string
3. Appending characters up to the remaining space
4. Always null-terminating the result
5. Returning the number of characters appended

### Time and Space Complexity
- Time Complexity: O(n) - where n is the length of the source string
- Space Complexity: O(1) - no additional space is used

### Edge Cases Handled
1. NULL pointers for either source or destination
2. Zero-size destination buffer
3. Destination buffer already full (for concatenation)
4. Empty source string
5. Source string longer than destination buffer

## Common Mistakes to Avoid
1. Not checking if dest_size is 0
2. Forgetting to null-terminate the destination string
3. Not handling NULL pointers
4. Off-by-one errors in buffer size calculation
5. Not returning correct count of copied/appended characters

## Best Practices
1. Always validate input parameters before processing
2. Leave space for null terminator when calculating buffer space
3. Use size_t for buffer sizes to handle large arrays correctly
4. Return meaningful error codes for invalid inputs
5. Document the behavior of the function clearly 