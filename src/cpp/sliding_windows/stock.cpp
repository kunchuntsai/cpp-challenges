/*
 * 121. Best Time to Buy and Sell Stock (Easy)
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
 *
 * Problem:
 * Given an array prices where prices[i] is the price of a given stock on the ith day,
 * find the maximum profit you can achieve from one transaction (buy one and sell one share of the stock).
 * If you cannot achieve any profit, return 0.
 *
 * Example 1:
 * Input: prices = [7,1,5,3,6,4]
 * Output: 5
 *
 * Example 2:
 * Input: prices = [7,6,4,3,1]
 * Output: 0
 *
 * Constraints:
 * - 1 <= prices.length <= 10^5
 * - 0 <= prices[i] <= 10^4
 */

#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>

class BestTimeToBuyAndSellStock {
public:
    /**
     * Finds the maximum profit from a single buy and sell transaction.
     *
     * @param prices Vector of stock prices by day
     * @return Maximum profit achievable
     *
     * Time Complexity: O(n), where n is the number of days
     * Space Complexity: O(1)
     */
    static int solve(const std::vector<int>& prices) {
        int min_price = INT_MAX;
        int max_profit = 0;
        for (int price : prices) {
            min_price = std::min(min_price, price);
            max_profit = std::max(max_profit, price - min_price);
        }
        return max_profit;
    }
};

void test_best_time_to_buy_and_sell_stock() {
    std::vector<int> prices1 = {7, 1, 5, 3, 6, 4};
    std::cout << "Test 1: [7,1,5,3,6,4] => " << BestTimeToBuyAndSellStock::solve(prices1) << " (Expected: 5)\n";
    std::vector<int> prices2 = {7, 6, 4, 3, 1};
    std::cout << "Test 2: [7,6,4,3,1] => " << BestTimeToBuyAndSellStock::solve(prices2) << " (Expected: 0)\n";
}

int main() {
    test_best_time_to_buy_and_sell_stock();
    return 0;
} 