/*
 * 55. Jump Game (Medium)
 * https://leetcode.com/problems/jump-game/
 *
 * Problem:
 * Given an array of non-negative integers nums, you are initially positioned at the first index of the array.
 * Each element in the array represents your maximum jump length at that position.
 * Determine if you are able to reach the last index.
 *
 * Example 1:
 * Input: nums = [2,3,1,1,4]
 * Output: true
 * Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
 *
 * Example 2:
 * Input: nums = [3,2,1,0,4]
 * Output: false
 * Explanation: You will always arrive at index 3 no matter what. Its maximum jump length is 0, which makes it impossible to reach the last index.
 *
 * Constraints:
 * - 1 <= nums.length <= 10^4
 * - 0 <= nums[i] <= 10^5
 */

#include <iostream>
#include <vector>

class JumpGame {
public:
    static bool solve(const std::vector<int>& nums) {
        int max_reach = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (i > max_reach) return false;
            max_reach = std::max(max_reach, i + nums[i]);
        }
        return true;
    }
};

void test_jump_game() {
    std::vector<std::pair<std::vector<int>, bool>> tests = {
        {{2,3,1,1,4}, true},
        {{3,2,1,0,4}, false},
        {{0}, true},
        {{2,0,0}, true},
        {{1,2,3}, true},
        {{1,0,1,0}, false}
    };
    for (const auto& [nums, expected] : tests) {
        std::cout << "Input: [";
        for (size_t i = 0; i < nums.size(); ++i) {
            std::cout << nums[i];
            if (i < nums.size() - 1) std::cout << ",";
        }
        std::cout << "]\nOutput: ";
        bool result = JumpGame::solve(nums);
        std::cout << (result ? "true" : "false") << "\nExpected: " << (expected ? "true" : "false") << std::endl;
        std::cout << ((result == expected) ? "PASS" : "FAIL") << "\n\n";
    }
}

int main() {
    test_jump_game();
    return 0;
}