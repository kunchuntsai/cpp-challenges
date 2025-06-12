#ifndef GROUP_ANAGRAMS_HPP
#define GROUP_ANAGRAMS_HPP

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

class GroupAnagrams {
public:
    // Time Complexity: O(n * k * log k) where n is number of strings and k is max string length
    // Space Complexity: O(n * k)
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

#endif // GROUP_ANAGRAMS_HPP 