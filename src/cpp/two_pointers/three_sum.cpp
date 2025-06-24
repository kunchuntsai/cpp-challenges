/*
 * 15. 3Sum (Medium)
 * https://leetcode.com/problems/3sum/
 *
 * Problem:
 * Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]]
 * such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.
 * Notice that the solution set must not contain duplicate triplets.
 *
 * Example 1:
 * Input: nums = [-1,0,1,2,-1,-4]
 * Output: [[-1,-1,2],[-1,0,1]]
 * Explanation:
 * nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
 * nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
 * nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
 * The distinct triplets are [-1,0,1] and [-1,-1,2].
 * Notice that the order of the output and the order of the triplets does not matter.
 *
 * Example 2:
 * Input: nums = []
 * Output: []
 *
 * Example 3:
 * Input: nums = [0]
 * Output: []
 *
 * Constraints:
 * - 3 <= nums.length <= 3000
 * - -10^5 <= nums[i] <= 10^5
 */

#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

class Solution {
public:
    /**
     * Finds all unique triplets in the array that sum up to zero.
     *
     * @param nums Vector of integers to analyze
     * @return Vector of vectors containing all unique triplets that sum to zero
     *
     * Time Complexity: O(n^2) where n is the length of nums
     * Space Complexity: O(1) excluding the output space
     */
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
        std::vector<std::vector<int>> result;
        int n = nums.size();

        // Sort the array to enable two-pointer technique, O(n log n)
        std::sort(nums.begin(), nums.end());

        // Iterate through each number as potential first element, Runs n-2 times ≈ O(n)
        for (int i = 0; i < n - 2; i++) {
            // Skip duplicates for the first element
            if (i > 0 && nums[i] == nums[i - 1]) continue;

            int left = i + 1;
            int right = n - 1;

            while (left < right) { // At most n steps per anchor
                int sum = nums[i] + nums[left] + nums[right];

                if (sum == 0) {
                    // Found a valid triplet
                    result.push_back({nums[i], nums[left], nums[right]});

                    // Skip duplicates for left pointer
                    while (left < right && nums[left] == nums[left + 1]) left++;
                    // Skip duplicates for right pointer
                    while (left < right && nums[right] == nums[right - 1]) right--;

                    left++;
                    right--;
                } else if (sum < 0) {
                    left++;
                } else {
                    right--;
                }
            }
        }

        return result;
    }
};

// Test cases
void runTests() {
    Solution solution;

    // Helper function to print vector of vectors
    auto printResult = [](const std::vector<std::vector<int>>& vec) {
        std::cout << "[";
        for (size_t i = 0; i < vec.size(); i++) {
            std::cout << "[";
            for (size_t j = 0; j < vec[i].size(); j++) {
                std::cout << vec[i][j];
                if (j < vec[i].size() - 1) std::cout << ",";
            }
            std::cout << "]";
            if (i < vec.size() - 1) std::cout << ",";
        }
        std::cout << "]" << std::endl;
    };

    // Test case 1: Basic case with multiple solutions
    {
        std::vector<int> nums = {-1, 0, 1, 2, -1, -4};
        std::vector<std::vector<int>> expected = {{-1, -1, 2}, {-1, 0, 1}};
        auto result = solution.threeSum(nums);
        std::cout << "Test case 1:" << std::endl;
        std::cout << "Input: [-1,0,1,2,-1,-4]" << std::endl;
        std::cout << "Expected: ";
        printResult(expected);
        std::cout << "Actual:   ";
        printResult(result);
        assert(result.size() == expected.size());
        std::cout << "Test case 1 passed!" << std::endl << std::endl;
    }

    // Test case 2: Empty array
    {
        std::vector<int> nums = {};
        std::vector<std::vector<int>> expected = {};
        auto result = solution.threeSum(nums);
        std::cout << "Test case 2:" << std::endl;
        std::cout << "Input: []" << std::endl;
        std::cout << "Expected: ";
        printResult(expected);
        std::cout << "Actual:   ";
        printResult(result);
        assert(result.size() == expected.size());
        std::cout << "Test case 2 passed!" << std::endl << std::endl;
    }

    // Test case 3: No solution
    {
        std::vector<int> nums = {1, 2, 3, 4};
        std::vector<std::vector<int>> expected = {};
        auto result = solution.threeSum(nums);
        std::cout << "Test case 3:" << std::endl;
        std::cout << "Input: [1,2,3,4]" << std::endl;
        std::cout << "Expected: ";
        printResult(expected);
        std::cout << "Actual:   ";
        printResult(result);
        assert(result.size() == expected.size());
        std::cout << "Test case 3 passed!" << std::endl << std::endl;
    }

    // Test case 4: All zeros
    {
        std::vector<int> nums = {0, 0, 0};
        std::vector<std::vector<int>> expected = {{0, 0, 0}};
        auto result = solution.threeSum(nums);
        std::cout << "Test case 4:" << std::endl;
        std::cout << "Input: [0,0,0]" << std::endl;
        std::cout << "Expected: ";
        printResult(expected);
        std::cout << "Actual:   ";
        printResult(result);
        assert(result.size() == expected.size());
        std::cout << "Test case 4 passed!" << std::endl << std::endl;
    }

    std::cout << "All test cases passed!" << std::endl;
}

int main() {
    runTests();
    return 0;
}