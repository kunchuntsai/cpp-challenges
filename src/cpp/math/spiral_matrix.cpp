/*
 * 54. Spiral Matrix (Medium)
 * https://leetcode.com/problems/spiral-matrix/
 *
 * Problem:
 * Given an m x n matrix, return all elements of the matrix in spiral order.
 *
 * Example 1:
 * Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
 * Output: [1,2,3,6,9,8,7,4,5]
 *
 * Example 2:
 * Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
 * Output: [1,2,3,4,8,12,11,10,9,5,6,7]
 *
 * Constraints:
 * - m == matrix.length
 * - n == matrix[i].length
 * - 1 <= m, n <= 10
 * - -100 <= matrix[i][j] <= 100
 */

#include <iostream>
#include <vector>

class SpiralMatrix {
public:
    /**
     * Returns all elements of the matrix in spiral order.
     *
     * Time Complexity: O(m * n)
     * Space Complexity: O(1) (output excluded)
     */
    static std::vector<int> solve(const std::vector<std::vector<int>>& matrix) {
        std::vector<int> res;
        if (matrix.empty()) return res;
        int m = matrix.size(), n = matrix[0].size();
        int top = 0, bottom = m - 1, left = 0, right = n - 1;
        while (top <= bottom && left <= right) {
            for (int j = left; j <= right; ++j) res.push_back(matrix[top][j]);
            ++top;
            for (int i = top; i <= bottom; ++i) res.push_back(matrix[i][right]);
            --right;
            if (top <= bottom) {
                for (int j = right; j >= left; --j) res.push_back(matrix[bottom][j]);
                --bottom;
            }
            if (left <= right) {
                for (int i = bottom; i >= top; --i) res.push_back(matrix[i][left]);
                ++left;
            }
        }
        return res;
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

void test_spiral_matrix() {
    std::vector<std::pair<std::vector<std::vector<int>>, std::vector<int>>> tests = {
        {{{1,2,3},{4,5,6},{7,8,9}}, {1,2,3,6,9,8,7,4,5}},
        {{{1,2,3,4},{5,6,7,8},{9,10,11,12}}, {1,2,3,4,8,12,11,10,9,5,6,7}}
    };
    for (const auto& [matrix, expected] : tests) {
        std::cout << "Input: matrix = ...\n";
        for (const auto& row : matrix) print_vector(row);
        auto result = SpiralMatrix::solve(matrix);
        std::cout << "Output: "; print_vector(result);
        std::cout << "Expected: "; print_vector(expected);
        std::cout << ((result == expected) ? "PASS" : "FAIL") << "\n";
    }
}

int main() {
    test_spiral_matrix();
    return 0;
}