/*
 * 62. Unique Paths (Medium)
 * https://leetcode.com/problems/unique-paths/
 *
 * Problem:
 * A robot is located at the top-left corner of an m x n grid (marked 'Start').
 * The robot can only move either down or right at any point in time.
 * The robot is trying to reach the bottom-right corner of the grid (marked 'Finish').
 * How many possible unique paths are there?
 *
 * Example 1:
 * Input: m = 3, n = 7
 * Output: 28
 *
 * Example 2:
 * Input: m = 3, n = 2
 * Output: 3
 *
 * Constraints:
 * - 1 <= m, n <= 100
 */

#include <iostream>
#include <vector>

class UniquePaths {
public:
    /**
     * Returns the number of unique paths in an m x n grid.
     *
     * Time Complexity: O(m * n)
     * Space Complexity: O(m * n)
     */
    static int solve(int m, int n) {
        std::vector<std::vector<int>> dp(m, std::vector<int>(n, 1));
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
        return dp[m-1][n-1];
    }
};

void test_unique_paths() {
    struct TestCase { int m, n, expected; };
    std::vector<TestCase> tests = {
        {3, 7, 28},
        {3, 2, 3},
        {7, 3, 28},
        {3, 3, 6},
        {1, 1, 1}
    };
    for (const auto& test : tests) {
        std::cout << "Input: m = " << test.m << ", n = " << test.n << std::endl;
        int result = UniquePaths::solve(test.m, test.n);
        std::cout << "Output: " << result << std::endl;
        std::cout << "Expected: " << test.expected << std::endl;
        std::cout << ((result == test.expected) ? "PASS" : "FAIL") << "\n";
    }
}

int main() {
    test_unique_paths();
    return 0;
}