/*
 * 76. Minimum Window Substring (Hard)
 * https://leetcode.com/problems/minimum-window-substring/
 *
 * Problem:
 * Given two strings s and t, return the minimum window in s which will contain all the characters in t.
 * If there is no such window in s that covers all characters in t, return the empty string "".
 *
 * Example 1:
 * Input: s = "ADOBECODEBANC", t = "ABC"
 * Output: "BANC"
 *
 * Example 2:
 * Input: s = "a", t = "a"
 * Output: "a"
 *
 * Example 3:
 * Input: s = "a", t = "aa"
 * Output: ""
 *
 * Constraints:
 * - 1 <= s.length, t.length <= 10^5
 * - s and t consist of English letters
 */

#include <string>
#include <unordered_map>
#include <climits>
#include <iostream>

class MinimumWindowSubstring {
public:
    /**
     * Returns the minimum window in s which contains all the characters in t.
     *
     * @param s The source string
     * @param t The target string
     * @return The minimum window substring
     *
     * Time Complexity: O(n + m), where n = s.length, m = t.length
     * Space Complexity: O(m)
     */
    static std::string solve(const std::string& s, const std::string& t) {
        std::unordered_map<char, int> need, window;
        for (char c : t) need[c]++;
        int have = 0, need_count = need.size();
        int left = 0, right = 0, min_len = INT_MAX, min_start = 0;
        while (right < s.size()) {
            char c = s[right++];
            window[c]++;
            if (need.count(c) && window[c] == need[c]) have++;
            while (have == need_count) {
                if (right - left < min_len) {
                    min_len = right - left;
                    min_start = left;
                }
                char d = s[left++];
                if (need.count(d) && window[d]-- == need[d]) have--;
            }
        }
        return min_len == INT_MAX ? "" : s.substr(min_start, min_len);
    }
};

void test_minimum_window_substring() {
    std::string s1 = "ADOBECODEBANC", t1 = "ABC";
    std::cout << "Test 1: s = 'ADOBECODEBANC', t = 'ABC' => '" << MinimumWindowSubstring::solve(s1, t1) << "' (Expected: 'BANC')\n";
    std::string s2 = "a", t2 = "a";
    std::cout << "Test 2: s = 'a', t = 'a' => '" << MinimumWindowSubstring::solve(s2, t2) << "' (Expected: 'a')\n";
    std::string s3 = "a", t3 = "aa";
    std::cout << "Test 3: s = 'a', t = 'aa' => '" << MinimumWindowSubstring::solve(s3, t3) << "' (Expected: '')\n";
}

int main() {
    test_minimum_window_substring();
    return 0;
}