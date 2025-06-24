/*
 * 136. Single Number (Easy)
 * https://leetcode.com/problems/single-number/
 *
 * Problem:
 * Given a non-empty array of integers nums, every element appears twice except for one. Find that single one.
 *
 * Example 1:
 * Input: nums = [2,2,1]
 * Output: 1
 *
 * Example 2:
 * Input: nums = [4,1,2,1,2]
 * Output: 4
 *
 * Constraints:
 * - 1 <= nums.length <= 3 * 10^4
 * - -3 * 10^4 <= nums[i] <= 3 * 10^4
 * - Each element in the array appears twice except for one element which appears only once.
 */

#include <iostream>
#include <vector>

class SingleNumber {
public:
    /**
     * Finds the single number using XOR properties.
     *
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    static int solve(const std::vector<int>& nums) {
        int res = 0;
        for (int num : nums) res ^= num;
        return res;
    }
};

void test_single_number() {
    std::vector<std::pair<std::vector<int>, int>> tests = {
        {{2,2,1}, 1},
        {{4,1,2,1,2}, 4},
        {{1}, 1}
    };
    for (const auto& [nums, expected] : tests) {
        std::cout << "Input: [";
        for (size_t i = 0; i < nums.size(); ++i) {
            std::cout << nums[i];
            if (i < nums.size() - 1) std::cout << ",";
        }
        std::cout << "]\nOutput: " << SingleNumber::solve(nums) << std::endl;
        std::cout << "Expected: " << expected << std::endl;
        std::cout << ((SingleNumber::solve(nums) == expected) ? "PASS" : "FAIL") << "\n";
    }
}

int main() {
    test_single_number();
    return 0;
}