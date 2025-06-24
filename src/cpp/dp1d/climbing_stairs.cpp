/*
 * 70. Climbing Stairs (Easy)
 * https://leetcode.com/problems/climbing-stairs/
 *
 * Problem:
 * You are climbing a staircase. It takes n steps to reach the top.
 * Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
 *
 * Example 1:
 * Input: n = 2
 * Output: 2
 *
 * Example 2:
 * Input: n = 3
 * Output: 3
 *
 * Constraints:
 * - 1 <= n <= 45
 */

#include <iostream>
#include <vector>

class ClimbingStairs {
public:
    /**
     * Returns the number of distinct ways to climb to the top.
     *
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    static int solve(int n) {
        if (n <= 2) return n;
        int prev1 = 2, prev2 = 1, curr = 0;
        for (int i = 3; i <= n; ++i) {
            curr = prev1 + prev2;
            prev2 = prev1;
            prev1 = curr;
        }
        return prev1;
    }
};

void test_climbing_stairs() {
    std::vector<std::pair<int, int>> tests = {
        {2, 2},
        {3, 3},
        {4, 5},
        {5, 8},
        {1, 1}
    };
    for (const auto& [n, expected] : tests) {
        std::cout << "Input: n = " << n << std::endl;
        int result = ClimbingStairs::solve(n);
        std::cout << "Output: " << result << std::endl;
        std::cout << "Expected: " << expected << std::endl;
        std::cout << ((result == expected) ? "PASS" : "FAIL") << "\n";
    }
}

int main() {
    test_climbing_stairs();
    return 0;
}