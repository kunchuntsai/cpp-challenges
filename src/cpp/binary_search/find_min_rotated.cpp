/*
 * 153. Find Minimum in Rotated Sorted Array (Medium)
 * https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/
 *
 * Problem:
 * Suppose an array of length n sorted in ascending order is rotated between 1 and n times. Return the minimum element of this array.
 *
 * Example 1:
 * Input: nums = [3,4,5,1,2]
 * Output: 1
 *
 * Example 2:
 * Input: nums = [4,5,6,7,0,1,2]
 * Output: 0
 *
 * Example 3:
 * Input: nums = [11,13,15,17]
 * Output: 11
 *
 * Constraints:
 * - n == nums.length
 * - 1 <= n <= 5000
 * - -5000 <= nums[i] <= 5000
 * - All the integers of nums are unique.
 * - nums is sorted and then rotated.
 */

#include <vector>
#include <iostream>

class FindMinRotated {
public:
    /**
     * Finds the minimum element in a rotated sorted array.
     *
     * @param nums Rotated sorted vector of integers
     * @return The minimum element
     *
     * Time Complexity: O(log n), where n is the length of nums
     * Space Complexity: O(1)
     */
    static int solve(const std::vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] > nums[right]) left = mid + 1;
            else right = mid;
        }
        return nums[left];
    }
};

void test_find_min_rotated() {
    std::vector<int> nums1 = {3,4,5,1,2};
    std::cout << "Test 1: [3,4,5,1,2] => " << FindMinRotated::solve(nums1) << " (Expected: 1)\n";
    std::vector<int> nums2 = {4,5,6,7,0,1,2};
    std::cout << "Test 2: [4,5,6,7,0,1,2] => " << FindMinRotated::solve(nums2) << " (Expected: 0)\n";
    std::vector<int> nums3 = {11,13,15,17};
    std::cout << "Test 3: [11,13,15,17] => " << FindMinRotated::solve(nums3) << " (Expected: 11)\n";
}

int main() {
    test_find_min_rotated();
    return 0;
} 