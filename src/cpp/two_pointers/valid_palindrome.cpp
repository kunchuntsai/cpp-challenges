/*
 * 125. Valid Palindrome (Easy)
 * https://leetcode.com/problems/valid-palindrome/
 *
 * Problem:
 * Given a string s, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.
 *
 * Example 1:
 * Input: s = "A man, a plan, a canal: Panama"
 * Output: true
 *
 * Example 2:
 * Input: s = "race a car"
 * Output: false
 *
 * Constraints:
 * - 1 <= s.length <= 2 * 10^5
 * - s consists only of printable ASCII characters.
 */

#include <iostream>
#include <string>
#include <cctype>
#include <vector>

class ValidPalindrome {
public:
    static bool solve(const std::string& s) {
        int left = 0, right = s.size() - 1;
        while (left < right) {
            while (left < right && !std::isalnum(s[left])) left++;
            while (left < right && !std::isalnum(s[right])) right--;
            if (std::tolower(s[left]) != std::tolower(s[right])) return false;
            left++;
            right--;
        }
        return true;
    }
};

void test_valid_palindrome() {
    std::vector<std::pair<std::string, bool>> tests = {
        {"A man, a plan, a canal: Panama", true},
        {"race a car", false},
        {"", true},
        {" ", true},
        {"0P", false},
        {"ab@a", true}
    };
    for (const auto& [input, expected] : tests) {
        bool result = ValidPalindrome::solve(input);
        std::cout << "Input: '" << input << "'\nOutput: " << (result ? "true" : "false") << "\nExpected: " << (expected ? "true" : "false") << "\n";
        std::cout << (result == expected ? "PASS" : "FAIL") << "\n\n";
    }
}

int main() {
    test_valid_palindrome();
    return 0;
} 