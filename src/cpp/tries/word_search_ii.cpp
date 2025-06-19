/*
 * 212. Word Search II (Hard)
 * https://leetcode.com/problems/word-search-ii/
 *
 * Problem:
 * Given an m x n board of characters and a list of strings words, return all words on the board.
 *
 * Example 1:
 * Input: board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], words = ["oath","pea","eat","rain"]
 * Output: ["eat","oath"]
 *
 * Example 2:
 * Input: board = [["a","b"],["c","d"]], words = ["abcb"]
 * Output: []
 *
 * Constraints:
 * - m == board.length
 * - n == board[i].length
 * - 1 <= m, n <= 12
 * - 1 <= words.length <= 3 * 10^4
 * - 1 <= words[i].length <= 10
 * - board and words[i] consist of lowercase English letters.
 */

#include <vector>
#include <string>
#include <iostream>

class WordSearchII {
    struct TrieNode {
        TrieNode* children[26] = {};
        std::string word = "";
    };
    TrieNode* root;
    std::vector<std::string> result;
public:
    WordSearchII() { root = new TrieNode(); }
    void insert(const std::string& word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) node->children[idx] = new TrieNode();
            node = node->children[idx];
        }
        node->word = word;
    }
    std::vector<std::string> solve(std::vector<std::vector<char>>& board, const std::vector<std::string>& words) {
        for (const std::string& word : words) insert(word);
        int m = board.size(), n = board[0].size();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                dfs(board, i, j, root);
            }
        }
        return result;
    }
private:
    void dfs(std::vector<std::vector<char>>& board, int i, int j, TrieNode* node) {
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size() || board[i][j] == '#') return;
        char c = board[i][j];
        TrieNode* next = node->children[c - 'a'];
        if (!next) return;
        if (!next->word.empty()) {
            result.push_back(next->word);
            next->word.clear();
        }
        board[i][j] = '#';
        dfs(board, i+1, j, next);
        dfs(board, i-1, j, next);
        dfs(board, i, j+1, next);
        dfs(board, i, j-1, next);
        board[i][j] = c;
    }
};

void print_result(const std::vector<std::string>& result) {
    std::cout << "[";
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << '"' << result[i] << '"';
        if (i < result.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n";
}

void test_word_search_ii() {
    std::vector<std::vector<char>> board1 = {{'o','a','a','n'},{'e','t','a','e'},{'i','h','k','r'},{'i','f','l','v'}};
    std::vector<std::string> words1 = {"oath","pea","eat","rain"};
    WordSearchII ws1;
    std::cout << "Test 1: => ";
    print_result(ws1.solve(board1, words1));
    std::cout << "(Expected: [\"eat\",\"oath\"])\n";
    std::vector<std::vector<char>> board2 = {{'a','b'},{'c','d'}};
    std::vector<std::string> words2 = {"abcb"};
    WordSearchII ws2;
    std::cout << "Test 2: => ";
    print_result(ws2.solve(board2, words2));
    std::cout << "(Expected: [])\n";
}

int main() {
    test_word_search_ii();
    return 0;
} 