/*
 * 49. Group Anagrams (Medium)
 * https://leetcode.com/problems/group-anagrams/
 *
 * Problem:
 * Given an array of strings strs, group the anagrams together. You can return
 * the answer in any order. An Anagram is a word or phrase formed by rearranging
 * the letters of a different word or phrase, typically using all the original
 * letters exactly once.
 *
 * Example 1:
 * Input: strs = ["eat","tea","tan","ate","nat","bat"]
 * Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
 *
 * Example 2:
 * Input: strs = [""]
 * Output: [[""]]
 *
 * Example 3:
 * Input: strs = ["a"]
 * Output: [["a"]]
 *
 * Constraints:
 * - 1 <= strs.length <= 10^4
 * - 0 <= strs[i].length <= 100
 * - strs[i] consists of lowercase English letters.
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include "test_utils.h"

class GroupAnagrams {
public:
    /**
     * Groups anagrams together from a list of strings.
     *
     * @param strs Vector of strings to group
     * @return Vector of vectors containing grouped anagrams
     *
     * Time Complexity: O(n * k * log k) where n is number of strings and k is max string length
     * Space Complexity: O(n * k)
     */
    static std::vector<std::vector<std::string>> solve(const std::vector<std::string>& strs) {
        std::unordered_map<std::string, std::vector<std::string>> anagramGroups;

        for (const std::string& str : strs) {
            std::string sortedStr = str;
            std::sort(sortedStr.begin(), sortedStr.end());
            anagramGroups[sortedStr].push_back(str);
        }

        std::vector<std::vector<std::string>> result;
        for (const auto& pair : anagramGroups) {
            result.push_back(pair.second);
        }

        return result;
    }
};

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