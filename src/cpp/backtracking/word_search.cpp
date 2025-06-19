/*
 * 79. Word Search (Medium)
 * https://leetcode.com/problems/word-search/
 *
 * Problem:
 * Given an m x n grid of characters board and a string word, return true if word exists in the grid.
 *
 * Example 1:
 * Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
 * Output: true
 *
 * Example 2:
 * Input: board = [["a","b"],["c","d"]], word = "abcd"
 * Output: false
 *
 * Constraints:
 * - m == board.length
 * - n = board[i].length
 * - 1 <= m, n <= 6
 * - 1 <= word.length <= 15
 * - board and word consists of only lowercase and uppercase English letters.
 */

#include <vector>
#include <string>
#include <iostream>

class WordSearch {
public:
    /**
     * Checks if a word exists in the board.
     *
     * @param board 2D grid of characters
     * @param word The word to search for
     * @return True if word exists, false otherwise
     *
     * Time Complexity: O(m * n * 3^L), where L is the length of word
     * Space Complexity: O(L)
     */
    static bool solve(std::vector<std::vector<char>>& board, const std::string& word) {
        int m = board.size(), n = board[0].size();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dfs(board, word, 0, i, j)) return true;
            }
        }
        return false;
    }
private:
    static bool dfs(std::vector<std::vector<char>>& board, const std::string& word, int idx, int i, int j) {
        if (idx == word.size()) return true;
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size() || board[i][j] != word[idx]) return false;
        char tmp = board[i][j];
        board[i][j] = '#';
        bool found = dfs(board, word, idx+1, i+1, j) || dfs(board, word, idx+1, i-1, j) ||
                     dfs(board, word, idx+1, i, j+1) || dfs(board, word, idx+1, i, j-1);
        board[i][j] = tmp;
        return found;
    }
};

void test_word_search() {
    std::vector<std::vector<char>> board1 = {{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}};
    std::cout << "Test 1: word='ABCCED' => " << (WordSearch::solve(board1, "ABCCED") ? "true" : "false") << " (Expected: true)\n";
    std::vector<std::vector<char>> board2 = {{'a','b'},{'c','d'}};
    std::cout << "Test 2: word='abcd' => " << (WordSearch::solve(board2, "abcd") ? "true" : "false") << " (Expected: false)\n";
}

int main() {
    test_word_search();
    return 0;
} 