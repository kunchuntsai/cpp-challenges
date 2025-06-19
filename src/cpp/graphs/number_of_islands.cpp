/*
 * 200. Number of Islands (Medium)
 * https://leetcode.com/problems/number-of-islands/
 *
 * Problem:
 * Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.
 *
 * Example 1:
 * Input: grid = [["1","1","1","1","0"],["1","1","0","1","0"],["1","1","0","0","0"],["0","0","0","0","0"]]
 * Output: 1
 *
 * Example 2:
 * Input: grid = [["1","1","0","0","0"],["1","1","0","0","0"],["0","0","1","0","0"],["0","0","0","1","1"]]
 * Output: 3
 *
 * Constraints:
 * - m == grid.length
 * - n == grid[i].length
 * - 1 <= m, n <= 300
 * - grid[i][j] is '0' or '1'.
 */

#include <vector>
#include <queue>
#include <iostream>

class NumberOfIslands {
public:
    /**
     * Returns the number of islands in the grid.
     *
     * @param grid 2D grid of '1's and '0's
     * @return Number of islands
     *
     * Time Complexity: O(m * n)
     * Space Complexity: O(m * n)
     */
    static int solve(std::vector<std::vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size(), count = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '1') {
                    dfs(grid, i, j);
                    ++count;
                }
            }
        }
        return count;
    }
private:
    static void dfs(std::vector<std::vector<char>>& grid, int i, int j) {
        if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() || grid[i][j] != '1') return;
        grid[i][j] = '0';
        dfs(grid, i+1, j);
        dfs(grid, i-1, j);
        dfs(grid, i, j+1);
        dfs(grid, i, j-1);
    }
};

void test_number_of_islands() {
    std::vector<std::vector<char>> grid1 = {{'1','1','1','1','0'},{'1','1','0','1','0'},{'1','1','0','0','0'},{'0','0','0','0','0'}};
    std::cout << "Test 1: => " << NumberOfIslands::solve(grid1) << " (Expected: 1)\n";
    std::vector<std::vector<char>> grid2 = {{'1','1','0','0','0'},{'1','1','0','0','0'},{'0','0','1','0','0'},{'0','0','0','1','1'}};
    std::cout << "Test 2: => " << NumberOfIslands::solve(grid2) << " (Expected: 3)\n";
}

int main() {
    test_number_of_islands();
    return 0;
} 