/*
 * 56. Merge Intervals (Medium)
 * https://leetcode.com/problems/merge-intervals/
 *
 * Problem:
 * Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals, and return an array of the non-overlapping intervals that cover all the intervals in the input.
 *
 * Example 1:
 * Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
 * Output: [[1,6],[8,10],[15,18]]
 *
 * Example 2:
 * Input: intervals = [[1,4],[4,5]]
 * Output: [[1,5]]
 *
 * Constraints:
 * - 1 <= intervals.length <= 10^4
 * - intervals[i].length == 2
 * - 0 <= starti <= endi <= 10^4
 */

#include <iostream>
#include <vector>
#include <algorithm>

class MergeIntervals {
public:
    /**
     * Merges all overlapping intervals.
     *
     * Time Complexity: O(n log n)
     * Space Complexity: O(n)
     */
    static std::vector<std::vector<int>> solve(std::vector<std::vector<int>> intervals) {
        if (intervals.empty()) return {};
        std::sort(intervals.begin(), intervals.end());
        std::vector<std::vector<int>> merged;
        merged.push_back(intervals[0]);
        for (size_t i = 1; i < intervals.size(); ++i) {
            if (intervals[i][0] <= merged.back()[1]) {
                merged.back()[1] = std::max(merged.back()[1], intervals[i][1]);
            } else {
                merged.push_back(intervals[i]);
            }
        }
        return merged;
    }
};

void print_intervals(const std::vector<std::vector<int>>& intervals) {
    std::cout << "[";
    for (size_t i = 0; i < intervals.size(); ++i) {
        std::cout << "[" << intervals[i][0] << "," << intervals[i][1] << "]";
        if (i < intervals.size() - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

void test_merge_intervals() {
    std::vector<std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>>> tests = {
        {{{1,3},{2,6},{8,10},{15,18}}, {{1,6},{8,10},{15,18}}},
        {{{1,4},{4,5}}, {{1,5}}},
        {{{1,4},{0,4}}, {{0,4}}},
        {{{1,4},{2,3}}, {{1,4}}},
        {{{1,4}}, {{1,4}}}
    };
    for (const auto& [intervals, expected] : tests) {
        std::cout << "Input: ";
        print_intervals(intervals);
        std::cout << "Output: ";
        auto result = MergeIntervals::solve(intervals);
        print_intervals(result);
        std::cout << "Expected: ";
        print_intervals(expected);
        std::cout << ((result == expected) ? "PASS" : "FAIL") << "\n";
    }
}

int main() {
    test_merge_intervals();
    return 0;
}