/*
 * 57. Insert Interval (Medium)
 * https://leetcode.com/problems/insert-interval/
 *
 * Problem:
 * You are given an array of non-overlapping intervals intervals where intervals[i] = [starti, endi] sorted by starti and a new interval newInterval = [start, end].
 * Insert newInterval into intervals such that intervals is still sorted by starti and merge overlapping intervals if necessary.
 *
 * Example 1:
 * Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
 * Output: [[1,5],[6,9]]
 *
 * Example 2:
 * Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
 * Output: [[1,2],[3,10],[12,16]]
 *
 * Constraints:
 * - 0 <= intervals.length <= 10^4
 * - intervals[i].length == 2
 * - 0 <= starti <= endi <= 10^5
 * - intervals are sorted by starti
 * - 0 <= start <= end <= 10^5
 */

#include <iostream>
#include <vector>

class InsertInterval {
public:
    /**
     * Inserts a new interval and merges if necessary.
     *
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     */
    static std::vector<std::vector<int>> solve(const std::vector<std::vector<int>>& intervals, const std::vector<int>& newInterval) {
        std::vector<std::vector<int>> result;
        size_t i = 0, n = intervals.size();
        // Add all intervals before newInterval
        while (i < n && intervals[i][1] < newInterval[0]) {
            result.push_back(intervals[i++]);
        }
        // Merge overlapping intervals
        std::vector<int> merged = newInterval;
        while (i < n && intervals[i][0] <= merged[1]) {
            merged[0] = std::min(merged[0], intervals[i][0]);
            merged[1] = std::max(merged[1], intervals[i][1]);
            ++i;
        }
        result.push_back(merged);
        // Add remaining intervals
        while (i < n) {
            result.push_back(intervals[i++]);
        }
        return result;
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

void test_insert_interval() {
    struct TestCase {
        std::vector<std::vector<int>> intervals;
        std::vector<int> newInterval;
        std::vector<std::vector<int>> expected;
    };
    std::vector<TestCase> tests = {
        {{{1,3},{6,9}}, {2,5}, {{1,5},{6,9}}},
        {{{1,2},{3,5},{6,7},{8,10},{12,16}}, {4,8}, {{1,2},{3,10},{12,16}}},
        {{{1,5}}, {2,3}, {{1,5}}},
        {{{1,5}}, {2,7}, {{1,7}}},
        {{}, {5,7}, {{5,7}}}
    };
    for (const auto& test : tests) {
        std::cout << "Input: intervals = ";
        print_intervals(test.intervals);
        std::cout << ", newInterval = [" << test.newInterval[0] << "," << test.newInterval[1] << "]" << std::endl;
        auto result = InsertInterval::solve(test.intervals, test.newInterval);
        std::cout << "Output: ";
        print_intervals(result);
        std::cout << "Expected: ";
        print_intervals(test.expected);
        std::cout << ((result == test.expected) ? "PASS" : "FAIL") << "\n";
    }
}

int main() {
    test_insert_interval();
    return 0;
}