/*
 * 704. Binary Search (Easy)
 * https://leetcode.com/problems/binary-search/
 *
 * Problem:
 * Given an array of integers nums which is sorted in ascending order, and an integer target, write a function to search target in nums. If target exists, return its index. Otherwise, return -1.
 *
 * Example 1:
 * Input: nums = [-1,0,3,5,9,12], target = 9
 * Output: 4
 *
 * Example 2:
 * Input: nums = [-1,0,3,5,9,12], target = 2
 * Output: -1
 *
 * Constraints:
 * - 1 <= nums.length <= 10^4
 * - -10^4 < nums[i], target < 10^4
 * - All the integers in nums are unique.
 * - nums is sorted in ascending order.
 */

#include <vector>
#include <iostream>

class BinarySearch {
public:
    /**
     * Performs binary search on a sorted array.
     *
     * @param nums Sorted vector of integers
     * @param target Target integer to search for
     * @return Index of target if found, -1 otherwise
     *
     * Time Complexity: O(log n), where n is the length of nums
     * Space Complexity: O(1)
     */
    static int solve(const std::vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) return mid;
            else if (nums[mid] < target) left = mid + 1;
            else right = mid - 1;
        }
        return -1;
    }
};

void test_binary_search() {
    std::vector<int> nums1 = {-1,0,3,5,9,12};
    std::cout << "Test 1: [-1,0,3,5,9,12], target = 9 => " << BinarySearch::solve(nums1, 9) << " (Expected: 4)\n";
    std::cout << "Test 2: [-1,0,3,5,9,12], target = 2 => " << BinarySearch::solve(nums1, 2) << " (Expected: -1)\n";
}

int main() {
    test_binary_search();
    return 0;
} 