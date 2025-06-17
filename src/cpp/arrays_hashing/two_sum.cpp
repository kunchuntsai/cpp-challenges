/*
 * 1. Two Sum (Easy)
 * https://leetcode.com/problems/two-sum/
 *
 * Problem:
 * Given an array of integers nums and an integer target, return indices of the
 * two numbers such that they add up to target. You may assume that each input
 * would have exactly one solution, and you may not use the same element twice.
 * You can return the answer in any order.
 *
 * Example 1:
 * Input: nums = [2,7,11,15], target = 9
 * Output: [0,1]
 * Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
 *
 * Example 2:
 * Input: nums = [3,2,4], target = 6
 * Output: [1,2]
 *
 * Example 3:
 * Input: nums = [3,3], target = 6
 * Output: [0,1]
 *
 * Constraints:
 * - 2 <= nums.length <= 10^4
 * - -10^9 <= nums[i] <= 10^9
 * - -10^9 <= target <= 10^9
 * - Only one valid answer exists.
 */
 
#include <iostream>
#include <vector>
#include <unordered_map>
#include "test_utils.h"

class TwoSum {
public:
    // Time Complexity: O(n)
    // Space Complexity: O(n)
    static std::vector<int> solve(const std::vector<int>& nums, int target) {
        std::unordered_map<int, int> numMap;

        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];

            if (numMap.find(complement) != numMap.end()) {
                return {numMap[complement], i};
            }

            numMap[nums[i]] = i;
        }

        return {}; // No solution found
    }
};

void test_two_sum() {
    std::cout << "\n=== Testing Two Sum ===\n";

    // Test Case 1: Basic case
    {
        std::vector<int> nums = {2, 7, 11, 15};
        int target = 9;
        std::cout << "\nTest Case 1:" << std::endl;
        std::cout << "Input: nums = [2, 7, 11, 15], target = " << target << std::endl;
        auto result = TwoSum::solve(nums, target);
        print_result(result);
    }

    // Test Case 2: Multiple possible solutions
    {
        std::vector<int> nums = {3, 2, 1, 6, 4};
        int target = 6;
        std::cout << "\nTest Case 2:" << std::endl;
        std::cout << "Input: nums = [3, 2, 1, 6, 4], target = " << target << std::endl;
        auto result = TwoSum::solve(nums, target);
        print_result(result);
    }

    // Test Case 3: Same number used twice
    {
        std::vector<int> nums = {3, 3};
        int target = 6;
        std::cout << "\nTest Case 3:" << std::endl;
        std::cout << "Input: nums = [3, 3], target = " << target << std::endl;
        auto result = TwoSum::solve(nums, target);
        print_result(result);
    }

    // Test Case 4: No solution
    {
        std::vector<int> nums = {1, 2, 3, 4};
        int target = 10;
        std::cout << "\nTest Case 4:" << std::endl;
        std::cout << "Input: nums = [1, 2, 3, 4], target = " << target << std::endl;
        auto result = TwoSum::solve(nums, target);
        print_result(result);
    }
}

int main() {
    test_two_sum();
    return 0;
}