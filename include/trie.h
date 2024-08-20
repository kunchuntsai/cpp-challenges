#ifndef TRIE_HPP
#define TRIE_HPP

#include <string>

using namespace std;

class TrieNode {
public:
    TrieNode* children[26];
    bool isEndOfWord;
    
    TrieNode() {
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
        isEndOfWord = false;
    }
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }
    
    void insert(string word) {
        TrieNode* current = root;
        for (char c : word) {
            int index = c - 'a';
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
            int index = c - 'a';
            if (current->children[index] == nullptr) {
                return nullptr;
            }
            current = current->children[index];
        }
        return current;
    }
};

#endif // TRIE_HPP