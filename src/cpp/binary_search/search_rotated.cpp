/*
 * 33. Search in Rotated Sorted Array (Medium)
 * https://leetcode.com/problems/search-in-rotated-sorted-array/
 *
 * Problem:
 * Given the array nums after the possible rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums.
 * You must write an algorithm with O(log n) runtime complexity.
 *
 * Example 1:
 * Input: nums = [4,5,6,7,0,1,2], target = 0
 * Output: 4
 *
 * Example 2:
 * Input: nums = [4,5,6,7,0,1,2], target = 3
 * Output: -1
 *
 * Example 3:
 * Input: nums = [1], target = 0
 * Output: -1
 *
 * Constraints:
 * - 1 <= nums.length <= 5000
 * - -10^4 <= nums[i] <= 10^4
 * - All values of nums are unique.
 * - nums is sorted and then rotated.
 */

#include <vector>
#include <iostream>

class SearchRotated {
public:
    /**
     * Searches for a target in a rotated sorted array.
     *
     * @param nums Rotated sorted vector of integers
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
            if (nums[left] <= nums[mid]) {
                if (nums[left] <= target && target < nums[mid]) right = mid - 1;
                else left = mid + 1;
            } else {
                if (nums[mid] < target && target <= nums[right]) left = mid + 1;
                else right = mid - 1;
            }
        }
        return -1;
    }
};

void test_search_rotated() {
    std::vector<int> nums1 = {4,5,6,7,0,1,2};
    std::cout << "Test 1: [4,5,6,7,0,1,2], target = 0 => " << SearchRotated::solve(nums1, 0) << " (Expected: 4)\n";
    std::cout << "Test 2: [4,5,6,7,0,1,2], target = 3 => " << SearchRotated::solve(nums1, 3) << " (Expected: -1)\n";
    std::vector<int> nums2 = {1};
    std::cout << "Test 3: [1], target = 0 => " << SearchRotated::solve(nums2, 0) << " (Expected: -1)\n";
}

int main() {
    test_search_rotated();
    return 0;
} 