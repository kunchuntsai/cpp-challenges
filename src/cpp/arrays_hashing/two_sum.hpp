#ifndef TWO_SUM_HPP
#define TWO_SUM_HPP

#include <vector>
#include <unordered_map>

class TwoSum {
public:
    // Time Complexity: O(n)
    // Space Complexity: O(n)
    static std::vector<int> solve(const std::vector<int>& nums, int target) {
        std::unordered_map<int, int> numMap;
        
        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            
            if (numMap.find(complement) != numMap.end()) {
                return {numMap[complement], i};
            }
            
            numMap[nums[i]] = i;
        }
        
        return {}; // No solution found
    }
};

#endif // TWO_SUM_HPP 