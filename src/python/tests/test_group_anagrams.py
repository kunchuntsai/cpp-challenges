import pytest
from problems.arrays_hashing.group_anagrams import Solution

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