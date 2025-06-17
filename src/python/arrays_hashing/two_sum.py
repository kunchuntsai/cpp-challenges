"""
1. Two Sum (Easy)
https://leetcode.com/problems/two-sum/

Problem:
Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
You may assume that each input would have exactly one solution, and you may not use the same element twice.
You can return the answer in any order.

Example 1:
Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].

Example 2:
Input: nums = [3,2,4], target = 6
Output: [1,2]

Example 3:
Input: nums = [3,3], target = 6
Output: [0,1]

Constraints:
- 2 <= nums.length <= 10^4
- -10^9 <= nums[i] <= 10^9
- -10^9 <= target <= 10^9
- Only one valid answer exists.
"""

from typing import List

class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        """
        Time Complexity: O(n)
        Space Complexity: O(n)
        
        Approach:
        1. Use a hash map to store numbers we've seen
        2. For each number, check if its complement (target - num) exists in the map
        3. If found, return the indices
        4. If not found, add current number and its index to the map
        """
        num_map = {}  # val -> index
        
        for i, num in enumerate(nums):
            complement = target - num
            if complement in num_map:
                return [num_map[complement], i]
            num_map[num] = i
        
        return []  # No solution found (though problem states there is always one)

# Example usage
if __name__ == "__main__":
    solution = Solution()
    
    # Test case 1
    nums1 = [2, 7, 11, 15]
    target1 = 9
    print(f"Input: nums = {nums1}, target = {target1}")
    print(f"Output: {solution.twoSum(nums1, target1)}")  # Expected: [0, 1]
    
    # Test case 2
    nums2 = [3, 2, 4]
    target2 = 6
    print(f"\nInput: nums = {nums2}, target = {target2}")
    print(f"Output: {solution.twoSum(nums2, target2)}")  # Expected: [1, 2]
    
    # Test case 3
    nums3 = [3, 3]
    target3 = 6
    print(f"\nInput: nums = {nums3}, target = {target3}")
    print(f"Output: {solution.twoSum(nums3, target3)}")  # Expected: [0, 1]

# Test cases
import pytest

@pytest.fixture
def solution():
    return Solution()

def test_two_sum_example1(solution):
    nums = [2, 7, 11, 15]
    target = 9
    result = solution.twoSum(nums, target)
    assert sorted(result) == [0, 1]

def test_two_sum_example2(solution):
    nums = [3, 2, 4]
    target = 6
    result = solution.twoSum(nums, target)
    assert sorted(result) == [1, 2]

def test_two_sum_example3(solution):
    nums = [3, 3]
    target = 6
    result = solution.twoSum(nums, target)
    assert sorted(result) == [0, 1]

def test_two_sum_negative_numbers(solution):
    nums = [-1, -2, -3, -4, -5]
    target = -8
    result = solution.twoSum(nums, target)
    assert sorted(result) == [2, 4]

def test_two_sum_duplicate_numbers(solution):
    nums = [1, 1, 1, 1]
    target = 2
    result = solution.twoSum(nums, target)
    assert len(result) == 2
    assert nums[result[0]] + nums[result[1]] == target 