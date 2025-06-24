/*
 * 739. Daily Temperatures (Medium)
 * https://leetcode.com/problems/daily-temperatures/
 *
 * Problem:
 * Given an array of integers temperatures represents the daily temperatures, return an array answer such that answer[i] is the number of days you have to wait after the ith day to get a warmer temperature. If there is no future day for this, put 0 instead.
 *
 * Example 1:
 * Input: temperatures = [73,74,75,71,69,72,76,73]
 * Output: [1,1,4,2,1,1,0,0]
 *
 * Example 2:
 * Input: temperatures = [30,40,50,60]
 * Output: [1,1,1,0]
 *
 * Example 3:
 * Input: temperatures = [30,60,90]
 * Output: [1,1,0]
 *
 * Constraints:
 * - 1 <= temperatures.length <= 10^5
 * - 30 <= temperatures[i] <= 100
 */

#include <vector>
#include <stack>
#include <iostream>

class DailyTemperatures {
public:
    /**
     * Returns the number of days to wait for a warmer temperature for each day.
     *
     * @param temperatures Vector of daily temperatures
     * @return Vector of days to wait for a warmer temperature
     *
     * Time Complexity: O(n), where n is the number of days
     * Space Complexity: O(n)
     */
    static std::vector<int> solve(const std::vector<int>& temperatures) {
        int n = temperatures.size();
        std::vector<int> answer(n, 0);
        std::stack<int> stk;
        for (int i = 0; i < n; ++i) {
            while (!stk.empty() && temperatures[i] > temperatures[stk.top()]) {
                int idx = stk.top(); stk.pop();
                answer[idx] = i - idx;
            }
            stk.push(i);
        }
        return answer;
    }
};

void print_result(const std::vector<int>& result) {
    std::cout << "[";
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << result[i];
        if (i < result.size() - 1) std::cout << ",";
    }
    std::cout << "]\n";
}

void test_daily_temperatures() {
    std::vector<int> t1 = {73,74,75,71,69,72,76,73};
    std::cout << "Test 1: [73,74,75,71,69,72,76,73] => ";
    print_result(DailyTemperatures::solve(t1));
    std::cout << "(Expected: [1,1,4,2,1,1,0,0])\n";
    std::vector<int> t2 = {30,40,50,60};
    std::cout << "Test 2: [30,40,50,60] => ";
    print_result(DailyTemperatures::solve(t2));
    std::cout << "(Expected: [1,1,1,0])\n";
    std::vector<int> t3 = {30,60,90};
    std::cout << "Test 3: [30,60,90] => ";
    print_result(DailyTemperatures::solve(t3));
    std::cout << "(Expected: [1,1,0])\n";
}

int main() {
    test_daily_temperatures();
    return 0;
}