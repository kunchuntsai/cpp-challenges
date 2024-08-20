#include "../include/trie.h"
#include "../include/unit_test.h"

void runTrieTests() {
    Trie trie;

    // Test 1: Insert and search words
    trie.insert("apple");
    assert(trie.search("apple") == true);
    assert(trie.search("app") == false);
    
    // Test 2: Insert more words
    trie.insert("app");
    trie.insert("apricot");
    assert(trie.search("app") == true);
    
    // Test 3: Search non-existent word
    assert(trie.search("apis") == false);
    
    // Test 4: startsWith tests
    assert(trie.startsWith("app") == true);
    assert(trie.startsWith("apr") == true);
    assert(trie.startsWith("b") == false);
    
    // Test 5: Empty string tests
    assert(trie.search("") == false);
    assert(trie.startsWith("") == true);
    
    // Test 6: Case sensitivity test
    trie.insert("Apple");
    assert(trie.search("apple") == true);
    assert(trie.search("Apple") == true);
    assert(trie.search("APPLE") == false);
    
    // Test 7: Long word test
    std::string longWord = "pneumonoultramicroscopicsilicovolcanoconiosis";
    trie.insert(longWord);
    assert(trie.search(longWord) == true);
    assert(trie.startsWith("pneumono") == true);
    
    // Test 8: Prefix is a word
    trie.insert("car");
    trie.insert("carpet");
    assert(trie.search("car") == true);
    assert(trie.startsWith("car") == true);
    
    // Test 9: Word is a prefix
    assert(trie.search("carpe") == false);
    assert(trie.startsWith("carpe") == true);

    std::cout << "All tests passed successfully!" << std::endl;
}
