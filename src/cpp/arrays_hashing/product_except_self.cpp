/*
 * 238. Product of Array Except Self (Medium)
 * https://leetcode.com/problems/product-of-array-except-self/
 *
 * Problem:
 * Given an integer array nums, return an array answer such that answer[i] is equal to the product of all the elements of nums except nums[i].
 * The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.
 * You must write an algorithm that runs in O(n) time and without using division.
 *
 * Example 1:
 * Input: nums = [1,2,3,4]
 * Output: [24,12,8,6]
 *
 * Example 2:
 * Input: nums = [-1,1,0,-3,3]
 * Output: [0,0,9,0,0]
 *
 * Constraints:
 * - 2 <= nums.length <= 10^5
 * - -30 <= nums[i] <= 30
 * - The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.
 */

#include <iostream>
#include <vector>

class ProductExceptSelf {
public:
    static std::vector<int> solve(const std::vector<int>& nums) {
        int n = nums.size();
        std::vector<int> answer(n, 1);
        int prefix = 1;
        for (int i = 0; i < n; ++i) {
            answer[i] = prefix;
            prefix *= nums[i];
        }
        int suffix = 1;
        for (int i = n - 1; i >= 0; --i) {
            answer[i] *= suffix;
            suffix *= nums[i];
        }
        return answer;
    }
};

void print_result(const std::vector<int>& result) {
    std::cout << "[";
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << result[i];
        if (i < result.size() - 1) std::cout << ",";
    }
    std::cout << "]\n";
}

void test_product_except_self() {
    std::vector<std::pair<std::vector<int>, std::vector<int>>> tests = {
        {{1,2,3,4}, {24,12,8,6}},
        {{-1,1,0,-3,3}, {0,0,9,0,0}},
        {{2,3,4,5}, {60,40,30,24}},
        {{0,0}, {0,0}},
        {{1,0}, {0,1}}
    };
    for (const auto& [nums, expected] : tests) {
        auto result = ProductExceptSelf::solve(nums);
        std::cout << "Input: [";
        for (size_t i = 0; i < nums.size(); ++i) {
            std::cout << nums[i];
            if (i < nums.size() - 1) std::cout << ",";
        }
        std::cout << "]\nOutput: ";
        print_result(result);
        std::cout << "Expected: ";
        print_result(expected);
        std::cout << ((result == expected) ? "PASS" : "FAIL") << "\n\n";
    }
}

int main() {
    test_product_except_self();
    return 0;
} 