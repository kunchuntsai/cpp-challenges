/*
 * 53. Maximum Subarray (Easy)
 * https://leetcode.com/problems/maximum-subarray/
 *
 * Problem:
 * Given an integer array nums, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.
 *
 * Example 1:
 * Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
 * Output: 6
 * Explanation: [4,-1,2,1] has the largest sum = 6.
 *
 * Example 2:
 * Input: nums = [1]
 * Output: 1
 *
 * Constraints:
 * - 1 <= nums.length <= 10^5
 * - -10^4 <= nums[i] <= 10^4
 */

#include <iostream>
#include <vector>

class MaximumSubarray {
public:
    /**
     * Finds the maximum sum of a contiguous subarray (Kadane's algorithm).
     *
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    static int solve(const std::vector<int>& nums) {
        int max_sum = nums[0];
        int curr_sum = nums[0];
        for (size_t i = 1; i < nums.size(); ++i) {
            curr_sum = std::max(nums[i], curr_sum + nums[i]);
            max_sum = std::max(max_sum, curr_sum);
        }
        return max_sum;
    }
};

void test_maximum_subarray() {
    std::vector<std::pair<std::vector<int>, int>> tests = {
        {{-2,1,-3,4,-1,2,1,-5,4}, 6},
        {{1}, 1},
        {{5,4,-1,7,8}, 23},
        {{-1,-2,-3,-4}, -1},
        {{1,2,3,4}, 10}
    };
    for (const auto& [nums, expected] : tests) {
        std::cout << "Input: [";
        for (size_t i = 0; i < nums.size(); ++i) {
            std::cout << nums[i];
            if (i < nums.size() - 1) std::cout << ",";
        }
        std::cout << "]\nOutput: ";
        int result = MaximumSubarray::solve(nums);
        std::cout << result << "\nExpected: " << expected << std::endl;
        std::cout << ((result == expected) ? "PASS" : "FAIL") << "\n\n";
    }
}

int main() {
    test_maximum_subarray();
    return 0;
}