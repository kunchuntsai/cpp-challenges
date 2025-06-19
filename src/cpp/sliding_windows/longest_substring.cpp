/*
 * 3. Longest Substring Without Repeating Characters (Medium)
 * https://leetcode.com/problems/longest-substring-without-repeating-characters/
 *
 * Problem:
 * Given a string s, find the length of the longest substring without repeating characters.
 *
 * Example 1:
 * Input: s = "abcabcbb"
 * Output: 3
 *
 * Example 2:
 * Input: s = "bbbbb"
 * Output: 1
 *
 * Example 3:
 * Input: s = "pwwkew"
 * Output: 3
 *
 * Constraints:
 * - 0 <= s.length <= 5 * 10^4
 * - s consists of English letters, digits, symbols and spaces.
 */

#include <string>
#include <unordered_set>
#include <iostream>

class LongestSubstringWithoutRepeatingCharacters {
public:
    /**
     * Returns the length of the longest substring without repeating characters.
     *
     * @param s Input string
     * @return Length of the longest substring without repeating characters
     *
     * Time Complexity: O(n), where n is the length of s
     * Space Complexity: O(min(n, m)), where m is the size of the charset/alphabet
     */
    static int solve(const std::string& s) {
        std::unordered_set<char> seen;
        int left = 0, right = 0, max_len = 0;
        while (right < s.size()) {
            if (seen.find(s[right]) == seen.end()) {
                seen.insert(s[right++]);
                max_len = std::max(max_len, right - left);
            } else {
                seen.erase(s[left++]);
            }
        }
        return max_len;
    }
};

void test_longest_substring_without_repeating_characters() {
    std::string s1 = "abcabcbb";
    std::cout << "Test 1: 'abcabcbb' => " << LongestSubstringWithoutRepeatingCharacters::solve(s1) << " (Expected: 3)\n";
    std::string s2 = "bbbbb";
    std::cout << "Test 2: 'bbbbb' => " << LongestSubstringWithoutRepeatingCharacters::solve(s2) << " (Expected: 1)\n";
    std::string s3 = "pwwkew";
    std::cout << "Test 3: 'pwwkew' => " << LongestSubstringWithoutRepeatingCharacters::solve(s3) << " (Expected: 3)\n";
}

int main() {
    test_longest_substring_without_repeating_characters();
    return 0;
} 