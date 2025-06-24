/*
 * 300. Longest Increasing Subsequence (Medium)
 * https://leetcode.com/problems/longest-increasing-subsequence/
 *
 * Problem:
 * Given an integer array nums, return the length of the longest strictly increasing subsequence.
 *
 * Example 1:
 * Input: nums = [10,9,2,5,3,7,101,18]
 * Output: 4
 *
 * Example 2:
 * Input: nums = [0,1,0,3,2,3]
 * Output: 4
 *
 * Constraints:
 * - 1 <= nums.length <= 2500
 * - -10^4 <= nums[i] <= 10^4
 */

#include <iostream>
#include <vector>
#include <algorithm>

class LongestIncreasingSubsequence {
public:
    /**
     * Returns the length of the longest strictly increasing subsequence (O(n^2) DP solution).
     *
     * Time Complexity: O(n^2)
     * Space Complexity: O(n)
     */
    static int solve_n2(const std::vector<int>& nums) {
        if (nums.empty()) return 0;
        std::vector<int> dp(nums.size(), 1);
        int max_len = 1;
        for (size_t i = 1; i < nums.size(); ++i) {
            for (size_t j = 0; j < i; ++j) {
                if (nums[i] > nums[j]) {
                    dp[i] = std::max(dp[i], dp[j] + 1);
                }
            }
            max_len = std::max(max_len, dp[i]);
        }
        return max_len;
    }

    /**
     * Returns the length of the longest strictly increasing subsequence (O(n log n) patience sorting solution).
     *
     * Time Complexity: O(n log n)
     * Space Complexity: O(n)
     */
    static int solve_nlogn(const std::vector<int>& nums) {
        std::vector<int> sub;
        for (int num : nums) {
            auto it = std::lower_bound(sub.begin(), sub.end(), num);
            if (it == sub.end()) sub.push_back(num);
            else *it = num;
        }
        return sub.size();
    }
};

void test_longest_increasing_subsequence() {
    std::vector<std::pair<std::vector<int>, int>> tests = {
        {{10,9,2,5,3,7,101,18}, 4},
        {{0,1,0,3,2,3}, 4},
        {{7,7,7,7,7,7,7}, 1},
        {{1,3,6,7,9,4,10,5,6}, 6}
    };
    for (const auto& [nums, expected] : tests) {
        std::cout << "Input: [";
        for (size_t i = 0; i < nums.size(); ++i) {
            std::cout << nums[i];
            if (i < nums.size() - 1) std::cout << ",";
        }
        std::cout << "]\nOutput (O(n^2)): " << LongestIncreasingSubsequence::solve_n2(nums) << std::endl;
        std::cout << "Output (O(n log n)): " << LongestIncreasingSubsequence::solve_nlogn(nums) << std::endl;
        std::cout << "Expected: " << expected << std::endl;
        std::cout << ((LongestIncreasingSubsequence::solve_nlogn(nums) == expected) ? "PASS" : "FAIL") << "\n";
    }
}

int main() {
    test_longest_increasing_subsequence();
    return 0;
}