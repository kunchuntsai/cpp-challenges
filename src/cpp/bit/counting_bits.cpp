/*
 * 338. Counting Bits (Medium)
 * https://leetcode.com/problems/counting-bits/
 *
 * Problem:
 * Given an integer n, return an array ans of length n + 1 such that for each i (0 <= i <= n), ans[i] is the number of 1's in the binary representation of i.
 *
 * Example 1:
 * Input: n = 2
 * Output: [0,1,1]
 *
 * Example 2:
 * Input: n = 5
 * Output: [0,1,1,2,1,2]
 *
 * Constraints:
 * - 0 <= n <= 10^5
 */

#include <iostream>
#include <vector>

class CountingBits {
public:
    /**
     * Returns an array where ans[i] is the number of 1's in the binary representation of i.
     *
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     */
    static std::vector<int> solve(int n) {
        std::vector<int> ans(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            ans[i] = ans[i >> 1] + (i & 1);
        }
        return ans;
    }
};

void print_vector(const std::vector<int>& v) {
    std::cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i];
        if (i < v.size() - 1) std::cout << ",";
    }
    std::cout << "]\n";
}

void test_counting_bits() {
    std::vector<std::pair<int, std::vector<int>>> tests = {
        {2, {0,1,1}},
        {5, {0,1,1,2,1,2}},
        {0, {0}}
    };
    for (const auto& [n, expected] : tests) {
        std::cout << "Input: n = " << n << std::endl;
        auto result = CountingBits::solve(n);
        std::cout << "Output: "; print_vector(result);
        std::cout << "Expected: "; print_vector(expected);
        std::cout << ((result == expected) ? "PASS" : "FAIL") << "\n";
    }
}

int main() {
    test_counting_bits();
    return 0;
}