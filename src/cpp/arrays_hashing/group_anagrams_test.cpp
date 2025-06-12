#include <iostream>
#include <vector>
#include <string>
#include "group_anagrams.hpp"

void print_anagram_groups(const std::vector<std::vector<std::string>>& groups) {
    std::cout << "Groups:" << std::endl;
    for (const auto& group : groups) {
        std::cout << "[";
        for (size_t i = 0; i < group.size(); ++i) {
            std::cout << "\"" << group[i] << "\"";
            if (i < group.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }
}

void test_group_anagrams() {
    std::cout << "\n=== Testing Group Anagrams ===\n";

    // Test Case 1: Basic case
    {
        std::vector<std::string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
        std::cout << "\nTest Case 1:" << std::endl;
        std::cout << "Input: [\"eat\", \"tea\", \"tan\", \"ate\", \"nat\", \"bat\"]" << std::endl;
        auto result = GroupAnagrams::solve(strs);
        print_anagram_groups(result);
    }

    // Test Case 2: Empty input
    {
        std::vector<std::string> strs = {};
        std::cout << "\nTest Case 2:" << std::endl;
        std::cout << "Input: []" << std::endl;
        auto result = GroupAnagrams::solve(strs);
        print_anagram_groups(result);
    }

    // Test Case 3: Single string
    {
        std::vector<std::string> strs = {"a"};
        std::cout << "\nTest Case 3:" << std::endl;
        std::cout << "Input: [\"a\"]" << std::endl;
        auto result = GroupAnagrams::solve(strs);
        print_anagram_groups(result);
    }
}

int main() {
    test_group_anagrams();
    return 0;
}