/*
 * 78. Subsets (Medium)
 * https://leetcode.com/problems/subsets/
 *
 * Problem:
 * Given an integer array nums of unique elements, return all possible subsets (the power set).
 *
 * Example 1:
 * Input: nums = [1,2,3]
 * Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
 *
 * Example 2:
 * Input: nums = [0]
 * Output: [[],[0]]
 *
 * Constraints:
 * - 1 <= nums.length <= 10
 * - -10 <= nums[i] <= 10
 * - All the numbers of nums are unique.
 */

#include <vector>
#include <iostream>

class Subsets {
public:
    /**
     * Returns all possible subsets of the input array.
     *
     * @param nums Vector of unique integers
     * @return Vector of all subsets
     *
     * Time Complexity: O(2^n * n)
     * Space Complexity: O(2^n * n)
     */
    static std::vector<std::vector<int>> solve(const std::vector<int>& nums) {
        std::vector<std::vector<int>> res;
        std::vector<int> curr;
        backtrack(nums, 0, curr, res);
        return res;
    }
private:
    static void backtrack(const std::vector<int>& nums, int start, std::vector<int>& curr, std::vector<std::vector<int>>& res) {
        res.push_back(curr);
        for (int i = start; i < nums.size(); ++i) {
            curr.push_back(nums[i]);
            backtrack(nums, i + 1, curr, res);
            curr.pop_back();
        }
    }
};

void print_result(const std::vector<std::vector<int>>& result) {
    std::cout << "[";
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << "[";
        for (size_t j = 0; j < result[i].size(); ++j) {
            std::cout << result[i][j];
            if (j < result[i].size() - 1) std::cout << ",";
        }
        std::cout << "]";
        if (i < result.size() - 1) std::cout << ",";
    }
    std::cout << "]\n";
}

void test_subsets() {
    std::vector<int> nums1 = {1,2,3};
    std::cout << "Test 1: [1,2,3] => ";
    print_result(Subsets::solve(nums1));
    std::cout << "(Expected: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]])\n";
    std::vector<int> nums2 = {0};
    std::cout << "Test 2: [0] => ";
    print_result(Subsets::solve(nums2));
    std::cout << "(Expected: [[],[0]])\n";
}

int main() {
    test_subsets();
    return 0;
}