#include <stdio.h>
#include <limits.h>

/**
 * Finds the maximum sum of a contiguous subarray using Kadane's algorithm
 * @param arr Input array
 * @param n Size of the array
 * @return Maximum sum of a contiguous subarray
 */
int maxSubArray(int arr[], int n) {
    int max_so_far = INT_MIN;  // Initialize with minimum possible value
    int max_ending_here = 0;   // Initialize current sum
    
    for (int i = 0; i < n; i++) {
        max_ending_here = max_ending_here + arr[i];
        
        // Update max_so_far if current sum is greater
        if (max_so_far < max_ending_here)
            max_so_far = max_ending_here;
        
        // If current sum becomes negative, reset it to 0
        if (max_ending_here < 0)
            max_ending_here = 0;
    }
    
    return max_so_far;
}

/**
 * Finds the maximum sum of a contiguous subarray and also returns the indices
 * @param arr Input array
 * @param n Size of the array
 * @param start Pointer to store the start index of the subarray
 * @param end Pointer to store the end index of the subarray
 * @return Maximum sum of a contiguous subarray
 */
int maxSubArrayWithIndices(int arr[], int n, int* start, int* end) {
    int max_so_far = INT_MIN;
    int max_ending_here = 0;
    int temp_start = 0;
    
    for (int i = 0; i < n; i++) {
        max_ending_here = max_ending_here + arr[i];
        
        // Update max_so_far if current sum is greater
        if (max_so_far < max_ending_here) {
            max_so_far = max_ending_here;
            *start = temp_start;
            *end = i;
        }
        
        // If current sum becomes negative, reset it to 0
        if (max_ending_here < 0) {
            max_ending_here = 0;
            temp_start = i + 1;
        }
    }
    
    return max_so_far;
}

// Test cases
int main() {
    // Test case 1: Basic case
    int arr1[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("Test Case 1:\n");
    printf("Array: ");
    for (int i = 0; i < n1; i++) {
        printf("%d ", arr1[i]);
    }
    printf("\nMaximum subarray sum: %d\n", maxSubArray(arr1, n1));
    
    // Test case 2: All negative numbers
    int arr2[] = {-2, -3, -4, -1, -2, -1, -5, -3};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("\nTest Case 2:\n");
    printf("Array: ");
    for (int i = 0; i < n2; i++) {
        printf("%d ", arr2[i]);
    }
    printf("\nMaximum subarray sum: %d\n", maxSubArray(arr2, n2));
    
    // Test case 3: All positive numbers
    int arr3[] = {1, 2, 3, 4, 5};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("\nTest Case 3:\n");
    printf("Array: ");
    for (int i = 0; i < n3; i++) {
        printf("%d ", arr3[i]);
    }
    printf("\nMaximum subarray sum: %d\n", maxSubArray(arr3, n3));
    
    // Test case 4: With indices
    int arr4[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    int start, end;
    int max_sum = maxSubArrayWithIndices(arr4, n4, &start, &end);
    printf("\nTest Case 4 (with indices):\n");
    printf("Array: ");
    for (int i = 0; i < n4; i++) {
        printf("%d ", arr4[i]);
    }
    printf("\nMaximum subarray sum: %d\n", max_sum);
    printf("Subarray indices: [%d, %d]\n", start, end);
    
    return 0;
} 