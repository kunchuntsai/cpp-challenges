/*
 * 215. Kth Largest Element in an Array (Medium)
 * https://leetcode.com/problems/kth-largest-element-in-an-array/
 *
 * Problem:
 * Given an integer array nums and an integer k, return the kth largest element in the array.
 *
 * Example 1:
 * Input: nums = [3,2,1,5,6,4], k = 2
 * Output: 5
 *
 * Example 2:
 * Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
 * Output: 4
 *
 * Constraints:
 * - 1 <= k <= nums.length <= 10^5
 * - -10^4 <= nums[i] <= 10^4
 */

#include <vector>
#include <queue>
#include <iostream>

class KthLargest {
public:
    /**
     * Finds the kth largest element in an array.
     *
     * @param nums Vector of integers
     * @param k The kth position
     * @return The kth largest element
     *
     * Time Complexity: O(n log k)
     * Space Complexity: O(k)
     */
    static int solve(const std::vector<int>& nums, int k) {
        std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
        for (int num : nums) {
            minHeap.push(num);
            if (minHeap.size() > k) minHeap.pop();
        }
        return minHeap.top();
    }
};

void test_kth_largest() {
    std::vector<int> nums1 = {3,2,1,5,6,4};
    std::cout << "Test 1: [3,2,1,5,6,4], k=2 => " << KthLargest::solve(nums1, 2) << " (Expected: 5)\n";
    std::vector<int> nums2 = {3,2,3,1,2,4,5,5,6};
    std::cout << "Test 2: [3,2,3,1,2,4,5,5,6], k=4 => " << KthLargest::solve(nums2, 4) << " (Expected: 4)\n";
}

int main() {
    test_kth_largest();
    return 0;
} 