/*
 * 134. Gas Station (Medium)
 * https://leetcode.com/problems/gas-station/
 *
 * Problem:
 * There are n gas stations along a circular route, where the amount of gas at the ith station is gas[i].
 * You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from the ith station to its next (i+1)th station.
 * You begin the journey with an empty tank at one of the gas stations.
 * Return the starting gas station's index if you can travel around the circuit once in the clockwise direction, otherwise return -1.
 *
 * Example 1:
 * Input: gas = [1,2,3,4,5], cost = [3,4,5,1,2]
 * Output: 3
 *
 * Example 2:
 * Input: gas = [2,3,4], cost = [3,4,3]
 * Output: -1
 *
 * Constraints:
 * - gas.length == n
 * - cost.length == n
 * - 1 <= n <= 10^5
 * - 0 <= gas[i], cost[i] <= 10^4
 */

#include <iostream>
#include <vector>

class GasStation {
public:
    static int solve(const std::vector<int>& gas, const std::vector<int>& cost) {
        int total = 0, curr = 0, start = 0;
        for (int i = 0; i < gas.size(); ++i) {
            int diff = gas[i] - cost[i];
            total += diff;
            curr += diff;
            if (curr < 0) {
                start = i + 1;
                curr = 0;
            }
        }
        return (total >= 0) ? start : -1;
    }
};

void test_gas_station() {
    struct TestCase {
        std::vector<int> gas;
        std::vector<int> cost;
        int expected;
    };
    std::vector<TestCase> tests = {
        {{1,2,3,4,5}, {3,4,5,1,2}, 3},
        {{2,3,4}, {3,4,3}, -1},
        {{5,1,2,3,4}, {4,4,1,5,1}, 4},
        {{2,0,1,2,3,4,0}, {0,1,0,0,0,0,11}, 0}
    };
    for (const auto& test : tests) {
        std::cout << "Input gas: [";
        for (size_t i = 0; i < test.gas.size(); ++i) {
            std::cout << test.gas[i];
            if (i < test.gas.size() - 1) std::cout << ",";
        }
        std::cout << "]\nInput cost: [";
        for (size_t i = 0; i < test.cost.size(); ++i) {
            std::cout << test.cost[i];
            if (i < test.cost.size() - 1) std::cout << ",";
        }
        std::cout << "]\nOutput: ";
        int result = GasStation::solve(test.gas, test.cost);
        std::cout << result << "\nExpected: " << test.expected << std::endl;
        std::cout << ((result == test.expected) ? "PASS" : "FAIL") << "\n\n";
    }
}

int main() {
    test_gas_station();
    return 0;
}