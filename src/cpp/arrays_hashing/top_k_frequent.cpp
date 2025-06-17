/*
 * 347. Top K Frequent Elements (Medium)
 * https://leetcode.com/problems/top-k-frequent-elements/
 *
 * Problem:
 * Given an integer array nums and an integer k, return the k most frequent
 * elements. You may return the answer in any order.
 *
 * Example 1:
 * Input: nums = [1,1,1,2,2,3], k = 2
 * Output: [1,2]
 *
 * Example 2:
 * Input: nums = [1], k = 1
 * Output: [1]
 *
 * Constraints:
 * - 1 <= nums.length <= 10^5
 * - -10^4 <= nums[i] <= 10^4
 * - k is in the range [1, the number of unique elements in the array].
 * - It is guaranteed that the answer is unique.
 */
 
#include <iostream>
#include <vector>
#include <unordered_map>
#include "test_utils.h"

class TopKFrequent {
public:
    /**
     * Finds the k most frequent elements in an array.
     * 
     * @param nums Vector of integers to analyze
     * @param k Number of most frequent elements to return
     * @return Vector containing the k most frequent elements
     * 
     * Time Complexity: O(n) where n is the length of nums
     * Space Complexity: O(n)
     */
    static std::vector<int> solve(const std::vector<int>& nums, int k) {
        // Count frequencies
        std::unordered_map<int, int> frequencyMap;
        for (int num : nums) {
            frequencyMap[num]++;
        }

        // Create buckets for frequencies
        std::vector<std::vector<int>> buckets(nums.size() + 1);
        for (const auto& pair : frequencyMap) {
            buckets[pair.second].push_back(pair.first);
        }

        // Get top k frequent elements
        std::vector<int> result;
        for (int i = buckets.size() - 1; i >= 0 && result.size() < k; i--) {
            for (int num : buckets[i]) {
                result.push_back(num);
                if (result.size() == k) break;
            }
        }

        return result;
    }
};

void test_top_k_frequent() {
    std::cout << "\n=== Testing Top K Frequent Elements ===\n";

    // Test Case 1: Basic case
    {
        std::vector<int> nums = {1, 1, 1, 2, 2, 3};
        int k = 2;
        std::cout << "\nTest Case 1:" << std::endl;
        std::cout << "Input: nums = [1, 1, 1, 2, 2, 3], k = " << k << std::endl;
        auto result = TopKFrequent::solve(nums, k);
        print_result(result);
    }

    // Test Case 2: Single element
    {
        std::vector<int> nums = {1};
        int k = 1;
        std::cout << "\nTest Case 2:" << std::endl;
        std::cout << "Input: nums = [1], k = " << k << std::endl;
        auto result = TopKFrequent::solve(nums, k);
        print_result(result);
    }

    // Test Case 3: All elements have same frequency
    {
        std::vector<int> nums = {1, 2, 3, 4, 5};
        int k = 3;
        std::cout << "\nTest Case 3:" << std::endl;
        std::cout << "Input: nums = [1, 2, 3, 4, 5], k = " << k << std::endl;
        auto result = TopKFrequent::solve(nums, k);
        print_result(result);
    }

    // Test Case 4: Negative numbers
    {
        std::vector<int> nums = {-1, -1, 2, 2, 2, 3, 3, 3, 3};
        int k = 2;
        std::cout << "\nTest Case 4:" << std::endl;
        std::cout << "Input: nums = [-1, -1, 2, 2, 2, 3, 3, 3, 3], k = " << k << std::endl;
        auto result = TopKFrequent::solve(nums, k);
        print_result(result);
    }
}

int main() {
    test_top_k_frequent();
    return 0;
}