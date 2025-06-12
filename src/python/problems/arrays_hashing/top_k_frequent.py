"""
347. Top K Frequent Elements (Medium)
https://leetcode.com/problems/top-k-frequent-elements/

Problem:
Given an integer array nums and an integer k, return the k most frequent elements.
You may return the answer in any order.

Example 1:
Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]

Example 2:
Input: nums = [1], k = 1
Output: [1]

Constraints:
- 1 <= nums.length <= 10^5
- -10^4 <= nums[i] <= 10^4
- k is in the range [1, the number of unique elements in the array].
- It is guaranteed that the answer is unique.
"""

from typing import List
from collections import Counter
import heapq

class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        """
        Time Complexity: O(n log k) where n is the length of nums
        Space Complexity: O(n)
        
        Approach:
        1. Count frequency of each number using Counter
        2. Use a min heap to keep track of k most frequent elements
        3. Return the k most frequent elements
        """
        # Count frequencies
        count = Counter(nums)
        
        # Use a min heap to keep track of k most frequent elements
        # Store (-frequency, number) to simulate max heap with min heap
        heap = []
        for num, freq in count.items():
            heapq.heappush(heap, (freq, num))
            if len(heap) > k:
                heapq.heappop(heap)
        
        # Extract numbers from heap
        return [num for _, num in heap]

    def topKFrequent_bucket_sort(self, nums: List[int], k: int) -> List[int]:
        """
        Alternative solution using bucket sort
        Time Complexity: O(n)
        Space Complexity: O(n)
        
        Approach:
        1. Count frequency of each number
        2. Create buckets where index represents frequency
        3. Collect numbers from highest frequency bucket to lowest
        """
        count = Counter(nums)
        n = len(nums)
        
        # Create buckets where index represents frequency
        buckets = [[] for _ in range(n + 1)]
        for num, freq in count.items():
            buckets[freq].append(num)
        
        # Collect numbers from highest frequency bucket to lowest
        result = []
        for i in range(n, 0, -1):
            result.extend(buckets[i])
            if len(result) >= k:
                return result[:k]
        
        return result

# Example usage
if __name__ == "__main__":
    solution = Solution()
    
    # Test case 1
    nums1 = [1, 1, 1, 2, 2, 3]
    k1 = 2
    print(f"Input: nums = {nums1}, k = {k1}")
    print(f"Output (heap): {solution.topKFrequent(nums1, k1)}")
    print(f"Output (bucket): {solution.topKFrequent_bucket_sort(nums1, k1)}")
    
    # Test case 2
    nums2 = [1]
    k2 = 1
    print(f"\nInput: nums = {nums2}, k = {k2}")
    print(f"Output (heap): {solution.topKFrequent(nums2, k2)}")
    print(f"Output (bucket): {solution.topKFrequent_bucket_sort(nums2, k2)}") 