#include "trie.h"
#include "unit_test.h"
#include <iostream>

TEST(TrieInsertAndSearch) {
    Trie trie;
    trie.insert("apple");
    ASSERT_TRUE(trie.search("apple"));
    ASSERT_FALSE(trie.search("app"));
}

TEST(TrieStartsWith) {
    Trie trie;
    trie.insert("apple");
    trie.insert("app");
    ASSERT_TRUE(trie.startsWith("app"));
    ASSERT_TRUE(trie.startsWith("appl"));
    ASSERT_FALSE(trie.startsWith("b"));
}

TEST(TrieEmptyString) {
    Trie trie;
    ASSERT_FALSE(trie.search(""));
    ASSERT_TRUE(trie.startsWith(""));
}

TEST(TrieCaseSensitivity) {
    Trie trie;
    trie.insert("Apple");
    ASSERT_TRUE(trie.search("Apple"));
    ASSERT_FALSE(trie.search("apple"));
    ASSERT_FALSE(trie.search("APPLE"));
}

TEST(TrieLongWord) {
    Trie trie;
    std::string longWord = "pneumonoultramicroscopicsilicovolcanoconiosis";
    trie.insert(longWord);
    ASSERT_TRUE(trie.search(longWord));
    ASSERT_TRUE(trie.startsWith("pneumono"));
}

void runTrieTests() {
    UnitTest::runAllTests();
}