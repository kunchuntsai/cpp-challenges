/*
 * 198. House Robber (Medium)
 * https://leetcode.com/problems/house-robber/
 *
 * Problem:
 * You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security systems connected and it will automatically contact the police if two adjacent houses were broken into on the same night.
 * Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob tonight without alerting the police.
 *
 * Example 1:
 * Input: nums = [1,2,3,1]
 * Output: 4
 *
 * Example 2:
 * Input: nums = [2,7,9,3,1]
 * Output: 12
 *
 * Constraints:
 * - 1 <= nums.length <= 100
 * - 0 <= nums[i] <= 400
 */

#include <iostream>
#include <vector>

class HouseRobber {
public:
    /**
     * Returns the maximum amount of money that can be robbed without alerting the police.
     *
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    static int solve(const std::vector<int>& nums) {
        if (nums.empty()) return 0;
        if (nums.size() == 1) return nums[0];
        int prev1 = nums[0], prev2 = std::max(nums[0], nums[1]);
        for (size_t i = 2; i < nums.size(); ++i) {
            int curr = std::max(prev2, prev1 + nums[i]);
            prev1 = prev2;
            prev2 = curr;
        }
        return prev2;
    }
};

void test_house_robber() {
    std::vector<std::pair<std::vector<int>, int>> tests = {
        {{1,2,3,1}, 4},
        {{2,7,9,3,1}, 12},
        {{2,1,1,2}, 4},
        {{1}, 1},
        {{}, 0}
    };
    for (const auto& [nums, expected] : tests) {
        std::cout << "Input: [";
        for (size_t i = 0; i < nums.size(); ++i) {
            std::cout << nums[i];
            if (i < nums.size() - 1) std::cout << ",";
        }
        std::cout << "]\nOutput: " << HouseRobber::solve(nums) << std::endl;
        std::cout << "Expected: " << expected << std::endl;
        std::cout << ((HouseRobber::solve(nums) == expected) ? "PASS" : "FAIL") << "\n";
    }
}

int main() {
    test_house_robber();
    return 0;
}