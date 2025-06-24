/*
 * 518. Coin Change 2 (Medium)
 * https://leetcode.com/problems/coin-change-2/
 *
 * Problem:
 * You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.
 * Return the number of combinations that make up that amount. You may assume that you have infinite number of each kind of coin.
 *
 * Example 1:
 * Input: amount = 5, coins = [1,2,5]
 * Output: 4
 * Explanation: there are four ways to make up the amount:
 * 5=5
 * 5=2+2+1
 * 5=2+1+1+1
 * 5=1+1+1+1+1
 *
 * Example 2:
 * Input: amount = 3, coins = [2]
 * Output: 0
 *
 * Constraints:
 * - 1 <= amount <= 5000
 * - 1 <= coins.length <= 500
 * - 1 <= coins[i] <= 5000
 * - All the values of coins are unique.
 */

#include <iostream>
#include <vector>

class CoinChange2 {
public:
    /**
     * Returns the number of combinations that make up the amount using given coins.
     *
     * Time Complexity: O(amount * n)
     * Space Complexity: O(amount)
     *   where n = number of coins
     */
    static int solve(int amount, const std::vector<int>& coins) {
        std::vector<int> dp(amount + 1, 0);
        dp[0] = 1;
        for (int coin : coins) {
            for (int i = coin; i <= amount; ++i) {
                dp[i] += dp[i - coin];
            }
        }
        return dp[amount];
    }
};

void test_coin_change_2() {
    struct TestCase { int amount; std::vector<int> coins; int expected; };
    std::vector<TestCase> tests = {
        {5, {1,2,5}, 4},
        {3, {2}, 0},
        {10, {10}, 1},
        {0, {1,2,3}, 1}
    };
    for (const auto& test : tests) {
        std::cout << "Input: amount = " << test.amount << ", coins = [";
        for (size_t i = 0; i < test.coins.size(); ++i) {
            std::cout << test.coins[i];
            if (i < test.coins.size() - 1) std::cout << ",";
        }
        std::cout << "]\n";
        int result = CoinChange2::solve(test.amount, test.coins);
        std::cout << "Output: " << result << std::endl;
        std::cout << "Expected: " << test.expected << std::endl;
        std::cout << ((result == test.expected) ? "PASS" : "FAIL") << "\n";
    }
}

int main() {
    test_coin_change_2();
    return 0;
}