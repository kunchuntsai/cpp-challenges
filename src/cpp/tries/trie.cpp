/*
 * 208. Implement Trie (Prefix Tree) (Medium)
 * https://leetcode.com/problems/implement-trie-prefix-tree/
 *
 * Problem:
 * Implement a trie with insert, search, and startsWith methods.
 *
 * Example 1:
 * Input: ["Trie","insert","search","search","startsWith","insert","search"], [[],["apple"],["apple"],["app"],["app"],["app"],["app"]]
 * Output: [null,null,true,false,true,null,true]
 *
 * Constraints:
 * - 1 <= word.length, prefix.length <= 2000
 * - word and prefix consist only of lowercase English letters.
 * - At most 3 * 10^4 calls will be made to insert, search, and startsWith.
 */

#include <string>
#include <vector>
#include <iostream>

class Trie {
    struct TrieNode {
        TrieNode* children[26] = {};
        bool isEnd = false;
    };
    TrieNode* root;
public:
    /**
     * Initializes the Trie object.
     *
     * Time Complexity: O(L) per operation, L = word/prefix length
     * Space Complexity: O(N), N = total number of nodes
     */
    Trie() { root = new TrieNode(); }

    void insert(const std::string& word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) node->children[idx] = new TrieNode();
            node = node->children[idx];
        }
        node->isEnd = true;
    }

    bool search(const std::string& word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) return false;
            node = node->children[idx];
        }
        return node->isEnd;
    }

    bool startsWith(const std::string& prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            int idx = c - 'a';
            if (!node->children[idx]) return false;
            node = node->children[idx];
        }
        return true;
    }
};

void test_trie() {
    Trie trie;
    trie.insert("apple");
    std::cout << "Test 1: search('apple') => " << (trie.search("apple") ? "true" : "false") << " (Expected: true)\n";
    std::cout << "Test 2: search('app') => " << (trie.search("app") ? "true" : "false") << " (Expected: false)\n";
    std::cout << "Test 3: startsWith('app') => " << (trie.startsWith("app") ? "true" : "false") << " (Expected: true)\n";
    trie.insert("app");
    std::cout << "Test 4: search('app') => " << (trie.search("app") ? "true" : "false") << " (Expected: true)\n";
}

int main() {
    test_trie();
    return 0;
} 