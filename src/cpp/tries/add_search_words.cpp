/*
 * 211. Design Add and Search Words Data Structure (Medium)
 * https://leetcode.com/problems/design-add-and-search-words-data-structure/
 *
 * Problem:
 * Implement the WordDictionary class with addWord and search (with '.' wildcard) methods.
 *
 * Example 1:
 * Input: ["WordDictionary","addWord","addWord","addWord","search","search","search","search"], [[],["bad"],["dad"],["mad"],["pad"],["bad"],[".ad"],["b.."]]
 * Output: [null,null,null,null,false,true,true,true]
 *
 * Constraints:
 * - 1 <= word.length <= 25
 * - word in addWord consists of lowercase English letters.
 * - word in search may contain '.'
 * - At most 10^4 calls will be made to addWord and search.
 */

#include <string>
#include <iostream>

class WordDictionary {
    struct TrieNode {
        TrieNode* children[26] = {};
        bool isEnd = false;
    };
    TrieNode* root;
public:
    /**
     * Initializes the WordDictionary object.
     *
     * Time Complexity: O(L) for addWord, O(26^L) for search worst case
     * Space Complexity: O(N), N = total number of nodes
     */
    WordDictionary() { root = new TrieNode(); }

    void addWord(const std::string& word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) node->children[idx] = new TrieNode();
            node = node->children[idx];
        }
        node->isEnd = true;
    }

    bool search(const std::string& word) {
        return searchHelper(word, 0, root);
    }
private:
    bool searchHelper(const std::string& word, int pos, TrieNode* node) {
        if (!node) return false;
        if (pos == word.size()) return node->isEnd;
        char c = word[pos];
        if (c == '.') {
            for (int i = 0; i < 26; ++i) {
                if (searchHelper(word, pos + 1, node->children[i])) return true;
            }
            return false;
        } else {
            return searchHelper(word, pos + 1, node->children[c - 'a']);
        }
    }
};

void test_add_search_words() {
    WordDictionary dict;
    dict.addWord("bad");
    dict.addWord("dad");
    dict.addWord("mad");
    std::cout << "Test 1: search('pad') => " << (dict.search("pad") ? "true" : "false") << " (Expected: false)\n";
    std::cout << "Test 2: search('bad') => " << (dict.search("bad") ? "true" : "false") << " (Expected: true)\n";
    std::cout << "Test 3: search('.ad') => " << (dict.search(".ad") ? "true" : "false") << " (Expected: true)\n";
    std::cout << "Test 4: search('b..') => " << (dict.search("b..") ? "true" : "false") << " (Expected: true)\n";
}

int main() {
    test_add_search_words();
    return 0;
}