"""
49. Group Anagrams (Medium)
https://leetcode.com/problems/group-anagrams/

Problem:
Given an array of strings strs, group the anagrams together. You can return the answer in any order.
An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase,
typically using all the original letters exactly once.

Example 1:
Input: strs = ["eat","tea","tan","ate","nat","bat"]
Output: [["bat"],["nat","tan"],["ate","eat","tea"]]

Example 2:
Input: strs = [""]
Output: [[""]]

Example 3:
Input: strs = ["a"]
Output: [["a"]]

Constraints:
- 1 <= strs.length <= 10^4
- 0 <= strs[i].length <= 100
- strs[i] consists of lowercase English letters.
"""

from typing import List
from collections import defaultdict

class Solution:
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        """
        Time Complexity: O(n * k * log k) where n is the number of strings and k is the max length of a string
        Space Complexity: O(n * k)
        
        Approach:
        1. Use a hash map where the key is the sorted string
        2. For each string, sort it and use it as a key
        3. Group all strings that have the same sorted key
        """
        anagram_groups = defaultdict(list)
        
        for s in strs:
            # Sort the string to create a key
            sorted_s = ''.join(sorted(s))
            # Add the original string to the group
            anagram_groups[sorted_s].append(s)
        
        # Return all groups
        return list(anagram_groups.values())

# Example usage
if __name__ == "__main__":
    solution = Solution()
    
    # Test case 1
    strs1 = ["eat", "tea", "tan", "ate", "nat", "bat"]
    print(f"Input: strs = {strs1}")
    result1 = solution.groupAnagrams(strs1)
    print("Output:", result1)
    
    # Test case 2
    strs2 = [""]
    print(f"\nInput: strs = {strs2}")
    result2 = solution.groupAnagrams(strs2)
    print("Output:", result2)
    
    # Test case 3
    strs3 = ["a"]
    print(f"\nInput: strs = {strs3}")
    result3 = solution.groupAnagrams(strs3)
    print("Output:", result3)

# Test cases
import pytest

@pytest.fixture
def solution():
    return Solution()

def test_group_anagrams_example1(solution):
    strs = ["eat", "tea", "tan", "ate", "nat", "bat"]
    result = solution.groupAnagrams(strs)
    # Sort each group and the result for consistent comparison
    result = [sorted(group) for group in result]
    result.sort()
    expected = [["bat"], ["nat", "tan"], ["ate", "eat", "tea"]]
    expected = [sorted(group) for group in expected]
    expected.sort()
    assert result == expected

def test_group_anagrams_example2(solution):
    strs = [""]
    result = solution.groupAnagrams(strs)
    assert result == [[""]]

def test_group_anagrams_example3(solution):
    strs = ["a"]
    result = solution.groupAnagrams(strs)
    assert result == [["a"]]

def test_group_anagrams_empty_input(solution):
    strs = []
    result = solution.groupAnagrams(strs)
    assert result == []

def test_group_anagrams_single_character(solution):
    strs = ["a", "b", "c"]
    result = solution.groupAnagrams(strs)
    # Sort each group and the result for consistent comparison
    result = [sorted(group) for group in result]
    result.sort()
    expected = [["a"], ["b"], ["c"]]
    expected = [sorted(group) for group in expected]
    expected.sort()
    assert result == expected 