/*
 * 435. Non-overlapping Intervals (Medium)
 * https://leetcode.com/problems/non-overlapping-intervals/
 *
 * Problem:
 * Given an array of intervals intervals where intervals[i] = [starti, endi], return the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.
 *
 * Example 1:
 * Input: intervals = [[1,2],[2,3],[3,4],[1,3]]
 * Output: 1
 *
 * Example 2:
 * Input: intervals = [[1,2],[1,2],[1,2]]
 * Output: 2
 *
 * Constraints:
 * - 1 <= intervals.length <= 2 * 10^4
 * - intervals[i].length == 2
 * - -2^31 <= starti < endi <= 2^31 - 1
 */

#include <iostream>
#include <vector>
#include <algorithm>

class NonOverlappingIntervals {
public:
    /**
     * Returns the minimum number of intervals to remove to make the rest non-overlapping.
     *
     * Time Complexity: O(n log n)
     * Space Complexity: O(1) (if sorting in-place)
     */
    static int solve(std::vector<std::vector<int>> intervals) {
        if (intervals.empty()) return 0;
        std::sort(intervals.begin(), intervals.end(), [](const auto& a, const auto& b) {
            return a[1] < b[1];
        });
        int count = 0, end = intervals[0][1];
        for (size_t i = 1; i < intervals.size(); ++i) {
            if (intervals[i][0] < end) {
                ++count;
            } else {
                end = intervals[i][1];
            }
        }
        return count;
    }
};

void test_non_overlapping_intervals() {
    std::vector<std::pair<std::vector<std::vector<int>>, int>> tests = {
        {{{1,2},{2,3},{3,4},{1,3}}, 1},
        {{{1,2},{1,2},{1,2}}, 2},
        {{{1,2},{2,3}}, 0},
        {{{1,100},{11,22},{1,11},{2,12}}, 2}
    };
    for (const auto& [intervals, expected] : tests) {
        std::cout << "Input: ";
        for (const auto& interval : intervals) {
            std::cout << "[" << interval[0] << "," << interval[1] << "] ";
        }
        std::cout << std::endl;
        int result = NonOverlappingIntervals::solve(intervals);
        std::cout << "Output: " << result << std::endl;
        std::cout << "Expected: " << expected << std::endl;
        std::cout << ((result == expected) ? "PASS" : "FAIL") << "\n";
    }
}

int main() {
    test_non_overlapping_intervals();
    return 0;
}