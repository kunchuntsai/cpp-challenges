#include <iostream>
#include <vector>
#include "top_k_frequent.hpp"
#include "test_utils.h"

void test_top_k_frequent() {
    std::cout << "\n=== Testing Top K Frequent Elements ===\n";
    
    // Test Case 1: Basic case
    {
        std::vector<int> nums = {1, 1, 1, 2, 2, 3};
        int k = 2;
        std::cout << "\nTest Case 1:" << std::endl;
        std::cout << "Input: nums = [1, 1, 1, 2, 2, 3], k = " << k << std::endl;
        auto result = TopKFrequent::solve(nums, k);
        print_result(result);
    }
    
    // Test Case 2: Single element
    {
        std::vector<int> nums = {1};
        int k = 1;
        std::cout << "\nTest Case 2:" << std::endl;
        std::cout << "Input: nums = [1], k = " << k << std::endl;
        auto result = TopKFrequent::solve(nums, k);
        print_result(result);
    }
    
    // Test Case 3: All elements have same frequency
    {
        std::vector<int> nums = {1, 2, 3, 4, 5};
        int k = 3;
        std::cout << "\nTest Case 3:" << std::endl;
        std::cout << "Input: nums = [1, 2, 3, 4, 5], k = " << k << std::endl;
        auto result = TopKFrequent::solve(nums, k);
        print_result(result);
    }
    
    // Test Case 4: Negative numbers
    {
        std::vector<int> nums = {-1, -1, 2, 2, 2, 3, 3, 3, 3};
        int k = 2;
        std::cout << "\nTest Case 4:" << std::endl;
        std::cout << "Input: nums = [-1, -1, 2, 2, 2, 3, 3, 3, 3], k = " << k << std::endl;
        auto result = TopKFrequent::solve(nums, k);
        print_result(result);
    }
}

int main() {
    test_top_k_frequent();
    return 0;
} 