/*
 * 73. Set Matrix Zeroes (Medium)
 * https://leetcode.com/problems/set-matrix-zeroes/
 *
 * Problem:
 * Given an m x n integer matrix, if an element is 0, set its entire row and column to 0's in-place.
 *
 * Example 1:
 * Input: matrix = [[1,1,1],[1,0,1],[1,1,1]]
 * Output: [[1,0,1],[0,0,0],[1,0,1]]
 *
 * Example 2:
 * Input: matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
 * Output: [[0,0,0,0],[0,4,5,0],[0,3,1,0]]
 *
 * Constraints:
 * - m == matrix.length
 * - n == matrix[0].length
 * - 1 <= m, n <= 200
 * - -2^31 <= matrix[i][j] <= 2^31 - 1
 */

#include <iostream>
#include <vector>

class SetMatrixZeroes {
public:
    /**
     * Sets entire row and column to 0 if an element is 0, in-place.
     *
     * Time Complexity: O(m * n)
     * Space Complexity: O(1) (in-place, ignoring input/output)
     */
    static void solve(std::vector<std::vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        bool firstRow = false, firstCol = false;
        for (int i = 0; i < m; ++i) if (matrix[i][0] == 0) firstCol = true;
        for (int j = 0; j < n; ++j) if (matrix[0][j] == 0) firstRow = true;
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }
        if (firstRow) for (int j = 0; j < n; ++j) matrix[0][j] = 0;
        if (firstCol) for (int i = 0; i < m; ++i) matrix[i][0] = 0;
    }
};

void print_matrix(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        std::cout << "[";
        for (size_t i = 0; i < row.size(); ++i) {
            std::cout << row[i];
            if (i < row.size() - 1) std::cout << ",";
        }
        std::cout << "]\n";
    }
}

void test_set_matrix_zeroes() {
    std::vector<std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>>> tests = {
        {{{1,1,1},{1,0,1},{1,1,1}}, {{1,0,1},{0,0,0},{1,0,1}}},
        {{{0,1,2,0},{3,4,5,2},{1,3,1,5}}, {{0,0,0,0},{0,4,5,0},{0,3,1,0}}}
    };
    for (auto& [matrix, expected] : tests) {
        std::cout << "Input: \n";
        print_matrix(matrix);
        SetMatrixZeroes::solve(matrix);
        std::cout << "Output: \n";
        print_matrix(matrix);
        std::cout << "Expected: \n";
        print_matrix(expected);
        std::cout << ((matrix == expected) ? "PASS" : "FAIL") << "\n";
    }
}

int main() {
    test_set_matrix_zeroes();
    return 0;
}