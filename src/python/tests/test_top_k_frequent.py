import pytest
from problems.arrays_hashing.top_k_frequent import Solution

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