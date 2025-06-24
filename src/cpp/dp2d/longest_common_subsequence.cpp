/*
 * 1143. Longest Common Subsequence (Medium)
 * https://leetcode.com/problems/longest-common-subsequence/
 *
 * Problem:
 * Given two strings text1 and text2, return the length of their longest common subsequence.
 *
 * Example 1:
 * Input: text1 = "abcde", text2 = "ace"
 * Output: 3
 * Explanation: The longest common subsequence is "ace" and its length is 3.
 *
 * Example 2:
 * Input: text1 = "abc", text2 = "abc"
 * Output: 3
 *
 * Constraints:
 * - 1 <= text1.length, text2.length <= 1000
 * - text1 and text2 consist of only lowercase English characters.
 */

#include <iostream>
#include <vector>
#include <string>

class LongestCommonSubsequence {
public:
    /**
     * Returns the length of the longest common subsequence between two strings.
     *
     * Time Complexity: O(m * n)
     * Space Complexity: O(m * n)
     *   where m = text1.length, n = text2.length
     */
    static int solve(const std::string& text1, const std::string& text2) {
        int m = text1.size(), n = text2.size();
        std::vector<std::vector<int>> dp(m+1, std::vector<int>(n+1, 0));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (text1[i-1] == text2[j-1])
                    dp[i][j] = dp[i-1][j-1] + 1;
                else
                    dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]);
            }
        }
        return dp[m][n];
    }
};

void test_longest_common_subsequence() {
    struct TestCase { std::string text1, text2; int expected; };
    std::vector<TestCase> tests = {
        {"abcde", "ace", 3},
        {"abc", "abc", 3},
        {"abc", "def", 0},
        {"bsbininm", "jmjkbkjkv", 1}
    };
    for (const auto& test : tests) {
        std::cout << "Input: text1 = '" << test.text1 << "', text2 = '" << test.text2 << "'\n";
        int result = LongestCommonSubsequence::solve(test.text1, test.text2);
        std::cout << "Output: " << result << std::endl;
        std::cout << "Expected: " << test.expected << std::endl;
        std::cout << ((result == test.expected) ? "PASS" : "FAIL") << "\n";
    }
}

int main() {
    test_longest_common_subsequence();
    return 0;
}