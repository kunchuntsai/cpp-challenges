#include <iostream>
#include <vector>
#include "two_sum.hpp"
#include "test_utils.h"

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
        std::vector<int> nums = {3, 2, 4};
        int target = 6;
        std::cout << "\nTest Case 2:" << std::endl;
        std::cout << "Input: nums = [3, 2, 4], target = " << target << std::endl;
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