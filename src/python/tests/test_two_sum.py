import pytest
from problems.arrays_hashing.two_sum import Solution

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