/*
 * 48. Rotate Image (Medium)
 * https://leetcode.com/problems/rotate-image/
 *
 * Problem:
 * You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise) in-place.
 *
 * Example 1:
 * Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
 * Output: [[7,4,1],[8,5,2],[9,6,3]]
 *
 * Example 2:
 * Input: matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
 * Output: [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]
 *
 * Constraints:
 * - n == matrix.length == matrix[i].length
 * - 1 <= n <= 20
 * - -1000 <= matrix[i][j] <= 1000
 */

#include <iostream>
#include <vector>
#include <algorithm>

class RotateImage {
public:
    /**
     * Rotates the matrix by 90 degrees clockwise in-place.
     *
     * Time Complexity: O(n^2)
     * Space Complexity: O(1)
     */
    static void solve(std::vector<std::vector<int>>& matrix) {
        int n = matrix.size();
        // Transpose
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                std::swap(matrix[i][j], matrix[j][i]);
            }
        }
        // Reverse each row
        for (int i = 0; i < n; ++i) {
            std::reverse(matrix[i].begin(), matrix[i].end());
        }
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

void test_rotate_image() {
    std::vector<std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>>> tests = {
        {{{1,2,3},{4,5,6},{7,8,9}}, {{7,4,1},{8,5,2},{9,6,3}}},
        {{{5,1,9,11},{2,4,8,10},{13,3,6,7},{15,14,12,16}}, {{15,13,2,5},{14,3,4,1},{12,6,8,9},{16,7,10,11}}}
    };
    for (auto& [matrix, expected] : tests) {
        std::cout << "Input: \n";
        print_matrix(matrix);
        RotateImage::solve(matrix);
        std::cout << "Output: \n";
        print_matrix(matrix);
        std::cout << "Expected: \n";
        print_matrix(expected);
        std::cout << ((matrix == expected) ? "PASS" : "FAIL") << "\n";
    }
}

int main() {
    test_rotate_image();
    return 0;
}