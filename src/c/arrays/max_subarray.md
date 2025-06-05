# Maximum Subarray Problem

## Problem Description
Given an integer array `nums`, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.

A subarray is a contiguous part of an array.

### Example 1:
```
Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: The subarray [4,-1,2,1] has the largest sum = 6.
```

### Example 2:
```
Input: nums = [1]
Output: 1
```

### Example 3:
```
Input: nums = [5,4,-1,7,8]
Output: 23
```

## Solution Approach

### Kadane's Algorithm
The most efficient solution to this problem is Kadane's Algorithm, which has a time complexity of O(n) and space complexity of O(1).

The algorithm works as follows:
1. Initialize two variables:
   - `max_so_far`: keeps track of the maximum sum found so far
   - `max_ending_here`: keeps track of the maximum sum ending at the current position

2. For each element in the array:
   - Add the current element to `max_ending_here`
   - If `max_ending_here` becomes negative, reset it to 0
   - Update `max_so_far` if `max_ending_here` is greater

### Implementation Details
The solution provides two functions:
1. `maxSubArray`: Returns only the maximum sum
2. `maxSubArrayWithIndices`: Returns both the maximum sum and the indices of the subarray

### Time and Space Complexity
- Time Complexity: O(n) - we only need to traverse the array once
- Space Complexity: O(1) - we only use a constant amount of extra space

### Edge Cases
1. All negative numbers: The algorithm will return the largest negative number
2. All positive numbers: The algorithm will return the sum of the entire array
3. Single element: The algorithm will return that element

## Usage
The implementation includes test cases demonstrating various scenarios:
1. Basic case with mixed positive and negative numbers
2. Array with all negative numbers
3. Array with all positive numbers
4. Case showing the indices of the maximum subarray

To compile and run:
```bash
gcc max_subarray.c -o max_subarray
./max_subarray
``` 