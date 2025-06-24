/*
 * 167. Two Sum II - Input Array Is Sorted (Medium)
 * https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/
 *
 * Problem:
 * Given a 1-indexed array of integers numbers that is already sorted in non-decreasing order, find two numbers such that they add up to a specific target number. Return the indices of the two numbers (1-indexed) as an integer array answer of size 2, where 1 <= answer[0] < answer[1] <= numbers.length.
 *
 * Example 1:
 * Input: numbers = [2,7,11,15], target = 9
 * Output: [1,2]
 *
 * Example 2:
 * Input: numbers = [2,3,4], target = 6
 * Output: [1,3]
 *
 * Example 3:
 * Input: numbers = [-1,0], target = -1
 * Output: [1,2]
 *
 * Constraints:
 * - 2 <= numbers.length <= 3 * 10^4
 * - -1000 <= numbers[i] <= 1000
 * - numbers is sorted in non-decreasing order.
 * - There is exactly one solution.
 */

#include <iostream>
#include <vector>

class TwoSumII {
public:
    static std::vector<int> solve(const std::vector<int>& numbers, int target) {
        int left = 0, right = numbers.size() - 1;
        while (left < right) {
            int sum = numbers[left] + numbers[right];
            if (sum == target) {
                return {left + 1, right + 1}; // 1-indexed
            } else if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
        return {};
    }
};

void test_two_sum_ii() {
    std::vector<std::tuple<std::vector<int>, int, std::vector<int>>> tests = {
        {{2,7,11,15}, 9, {1,2}},
        {{2,3,4}, 6, {1,3}},
        {{-1,0}, -1, {1,2}},
        {{1,2,3,4,4,9,56,90}, 8, {4,5}}
    };
    for (const auto& [numbers, target, expected] : tests) {
        auto result = TwoSumII::solve(numbers, target);
        std::cout << "Input: numbers = [";
        for (size_t i = 0; i < numbers.size(); ++i) {
            std::cout << numbers[i];
            if (i < numbers.size() - 1) std::cout << ",";
        }
        std::cout << "], target = " << target << "\nOutput: [";
        for (size_t i = 0; i < result.size(); ++i) {
            std::cout << result[i];
            if (i < result.size() - 1) std::cout << ",";
        }
        std::cout << "]\nExpected: [";
        for (size_t i = 0; i < expected.size(); ++i) {
            std::cout << expected[i];
            if (i < expected.size() - 1) std::cout << ",";
        }
        std::cout << "]\n";
        std::cout << (result == expected ? "PASS" : "FAIL") << "\n\n";
    }
}

int main() {
    test_two_sum_ii();
    return 0;
}