/*
 * 20. Valid Parentheses (Easy)
 * https://leetcode.com/problems/valid-parentheses/
 *
 * Problem:
 * Given a string s containing just the characters '(', ')', '{', '}', '[' and ']',
 * determine if the input string is valid.
 * An input string is valid if:
 *   1. Open brackets must be closed by the same type of brackets.
 *   2. Open brackets must be closed in the correct order.
 *
 * Example 1:
 * Input: s = "()"
 * Output: true
 *
 * Example 2:
 * Input: s = "()[]{}"
 * Output: true
 *
 * Example 3:
 * Input: s = "(]"
 * Output: false
 *
 * Constraints:
 * - 1 <= s.length <= 10^4
 * - s consists of parentheses only '()[]{}'.
 */

#include <string>
#include <stack>
#include <unordered_map>
#include <iostream>

class ValidParentheses {
public:
    /**
     * Checks if the input string has valid parentheses.
     *
     * @param s Input string
     * @return True if valid, false otherwise
     *
     * Time Complexity: O(n), where n is the length of s
     * Space Complexity: O(n)
     */
    static bool solve(const std::string& s) {
        std::stack<char> stk;
        std::unordered_map<char, char> pairs = {{')', '('}, {']', '['}, {'}', '{'}};
        for (char c : s) {
            if (pairs.count(c)) {
                if (stk.empty() || stk.top() != pairs[c]) return false;
                stk.pop();
            } else {
                stk.push(c);
            }
        }
        return stk.empty();
    }
};

void test_valid_parentheses() {
    std::string s1 = "()";
    std::cout << "Test 1: '()' => " << (ValidParentheses::solve(s1) ? "true" : "false") << " (Expected: true)\n";
    std::string s2 = "()[]{}";
    std::cout << "Test 2: '()[]{}' => " << (ValidParentheses::solve(s2) ? "true" : "false") << " (Expected: true)\n";
    std::string s3 = "(]";
    std::cout << "Test 3: '(]' => " << (ValidParentheses::solve(s3) ? "true" : "false") << " (Expected: false)\n";
}

int main() {
    test_valid_parentheses();
    return 0;
}