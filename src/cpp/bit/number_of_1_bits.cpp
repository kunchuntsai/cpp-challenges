/*
 * 191. Number of 1 Bits (Easy)
 * https://leetcode.com/problems/number-of-1-bits/
 *
 * Problem:
 * Write a function that takes the binary representation of an unsigned integer and returns the number of '1' bits it has (also known as the Hamming weight).
 *
 * Example 1:
 * Input: n = 11 (00000000000000000000000000001011)
 * Output: 3
 *
 * Example 2:
 * Input: n = 128 (00000000000000000000000010000000)
 * Output: 1
 *
 * Constraints:
 * - The input must be a binary string of length 32.
 */

#include <iostream>
#include <vector>

class NumberOf1Bits {
public:
    /**
     * Returns the number of '1' bits in the binary representation of n.
     *
     * Time Complexity: O(1) (since n is 32 bits)
     * Space Complexity: O(1)
     */
    static int solve(uint32_t n) {
        int count = 0;
        while (n) {
            n &= (n - 1);
            ++count;
        }
        return count;
    }
};

void test_number_of_1_bits() {
    std::vector<std::pair<uint32_t, int>> tests = {
        {11, 3},
        {128, 1},
        {4294967293, 31}
    };
    for (const auto& [n, expected] : tests) {
        std::cout << "Input: n = " << n << std::endl;
        int result = NumberOf1Bits::solve(n);
        std::cout << "Output: " << result << std::endl;
        std::cout << "Expected: " << expected << std::endl;
        std::cout << ((result == expected) ? "PASS" : "FAIL") << "\n";
    }
}

int main() {
    test_number_of_1_bits();
    return 0;
}