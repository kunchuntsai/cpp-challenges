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

# Test cases
import pytest

@pytest.fixture
def solution():
    return Solution()

def test_top_k_frequent_example1(solution):
    nums = [1, 1, 1, 2, 2, 3]
    k = 2
    result = solution.topKFrequent(nums, k)
    assert sorted(result) == [1, 2]
    
    # Test bucket sort solution
    result_bucket = solution.topKFrequent_bucket_sort(nums, k)
    assert sorted(result_bucket) == [1, 2]

def test_top_k_frequent_example2(solution):
    nums = [1]
    k = 1
    result = solution.topKFrequent(nums, k)
    assert result == [1]
    
    # Test bucket sort solution
    result_bucket = solution.topKFrequent_bucket_sort(nums, k)
    assert result_bucket == [1]

def test_top_k_frequent_negative_numbers(solution):
    nums = [-1, -1, 2, 2, 2, 3]
    k = 2
    result = solution.topKFrequent(nums, k)
    assert sorted(result) == [2, -1]
    
    # Test bucket sort solution
    result_bucket = solution.topKFrequent_bucket_sort(nums, k)
    assert sorted(result_bucket) == [2, -1]

def test_top_k_frequent_equal_frequencies(solution):
    nums = [1, 2, 3, 4]
    k = 2
    result = solution.topKFrequent(nums, k)
    assert len(result) == 2
    assert all(x in [1, 2, 3, 4] for x in result)
    
    # Test bucket sort solution
    result_bucket = solution.topKFrequent_bucket_sort(nums, k)
    assert len(result_bucket) == 2
    assert all(x in [1, 2, 3, 4] for x in result_bucket)

def test_top_k_frequent_all_same_numbers(solution):
    nums = [1, 1, 1, 1]
    k = 1
    result = solution.topKFrequent(nums, k)
    assert result == [1]
    
    # Test bucket sort solution
    result_bucket = solution.topKFrequent_bucket_sort(nums, k)
    assert result_bucket == [1] 