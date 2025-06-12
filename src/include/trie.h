#ifndef TRIE_HPP
#define TRIE_HPP

#include <string>
#include <cctype>

using namespace std;

class TrieNode {
public:
    TrieNode* children[52];  // 26 for lowercase + 26 for uppercase
    bool isEndOfWord;

    TrieNode() {
        for (int i = 0; i < 52; i++) {
            children[i] = nullptr;
        }
        isEndOfWord = false;
    }
};

class Trie {
private:
    TrieNode* root;

    int getIndex(char c) {
        if (c >= 'a' && c <= 'z') {
            return c - 'a';
        } else if (c >= 'A' && c <= 'Z') {
            return c - 'A' + 26;
        }
        return -1;  // Invalid character
    }

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(string word) {
        TrieNode* current = root;
        for (char c : word) {
            int index = getIndex(c);
            if (index < 0) continue;  // Skip non-alphabetic characters
            if (current->children[index] == nullptr) {
                current->children[index] = new TrieNode();
            }
            current = current->children[index];
        }
        current->isEndOfWord = true;
    }

    bool search(string word) {
        TrieNode* node = findNode(word);
        return (node != nullptr && node->isEndOfWord);
    }

    bool startsWith(string prefix) {
        return (findNode(prefix) != nullptr);
    }

private:
    TrieNode* findNode(string& s) {
        TrieNode* current = root;
        for (char c : s) {
            int index = getIndex(c);
            if (index < 0) return nullptr;  // Return null for non-alphabetic characters
            if (current->children[index] == nullptr) {
                return nullptr;
            }
            current = current->children[index];
        }
        return current;
    }
};

#endif // TRIE_HPP