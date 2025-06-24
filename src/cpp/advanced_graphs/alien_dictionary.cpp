/*
 * 269. Alien Dictionary (Hard)
 * https://leetcode.com/problems/alien-dictionary/
 *
 * Problem:
 * There is a new alien language that uses the English alphabet. However, the order among letters is unknown to you.
 * You are given a list of strings words from the alien language's dictionary, where the strings in words are sorted lexicographically by the rules of this new language.
 * Derive the order of letters in this language. Return a string of the unique letters in the new alien language in any valid order. If there is no solution, return "".
 *
 * Example 1:
 * Input: words = ["wrt","wrf","er","ett","rftt"]
 * Output: "wertf"
 *
 * Example 2:
 * Input: words = ["z","x"]
 * Output: "zx"
 *
 * Example 3:
 * Input: words = ["z","x","z"]
 * Output: ""
 *
 * Constraints:
 * - 1 <= words.length <= 100
 * - 1 <= words[i].length <= 100
 * - words[i] consists of only lowercase English letters.
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>

class AlienDictionary {
public:
    /**
     * Returns a string representing the order of letters in the alien language using topological sort.
     *
     * Time Complexity: O(C)
     * Space Complexity: O(C)
     *   where C = total number of characters in all words
     */
    static std::string solve(const std::vector<std::string>& words) {
        std::unordered_map<char, std::unordered_set<char>> adj;
        std::unordered_map<char, int> indegree;
        for (const auto& word : words) {
            for (char c : word) indegree[c] = 0;
        }
        for (size_t i = 0; i + 1 < words.size(); ++i) {
            const std::string& w1 = words[i];
            const std::string& w2 = words[i+1];
            size_t len = std::min(w1.size(), w2.size());
            bool found = false;
            for (size_t j = 0; j < len; ++j) {
                if (w1[j] != w2[j]) {
                    if (!adj[w1[j]].count(w2[j])) {
                        adj[w1[j]].insert(w2[j]);
                        indegree[w2[j]]++;
                    }
                    found = true;
                    break;
                }
            }
            if (!found && w1.size() > w2.size()) return "";
        }
        std::queue<char> q;
        for (const auto& [c, deg] : indegree) {
            if (deg == 0) q.push(c);
        }
        std::string order;
        while (!q.empty()) {
            char c = q.front(); q.pop();
            order += c;
            for (char nei : adj[c]) {
                if (--indegree[nei] == 0) q.push(nei);
            }
        }
        return order.size() == indegree.size() ? order : "";
    }
};

void test_alien_dictionary() {
    struct TestCase {
        std::vector<std::string> words;
        std::string expected;
    };
    std::vector<TestCase> tests = {
        {{"wrt","wrf","er","ett","rftt"}, "wertf"},
        {{"z","x"}, "zx"},
        {{"z","x","z"}, ""},
        {{"abc","ab"}, ""}
    };
    for (const auto& test : tests) {
        std::cout << "Input: words = [";
        for (size_t i = 0; i < test.words.size(); ++i) {
            std::cout << '"' << test.words[i] << '"';
            if (i < test.words.size() - 1) std::cout << ", ";
        }
        std::cout << "]\n";
        std::string result = AlienDictionary::solve(test.words);
        std::cout << "Output: " << result << std::endl;
        std::cout << "Expected: " << test.expected << std::endl;
        std::cout << ((result == test.expected) ? "PASS" : "FAIL") << "\n";
    }
}

int main() {
    test_alien_dictionary();
    return 0;
}