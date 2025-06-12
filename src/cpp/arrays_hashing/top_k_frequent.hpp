#ifndef TOP_K_FREQUENT_HPP
#define TOP_K_FREQUENT_HPP

#include <vector>
#include <unordered_map>

class TopKFrequent {
public:
    // Time Complexity: O(n)
    // Space Complexity: O(n)
    static std::vector<int> solve(const std::vector<int>& nums, int k) {
        // Count frequencies
        std::unordered_map<int, int> frequencyMap;
        for (int num : nums) {
            frequencyMap[num]++;
        }

        // Create buckets for frequencies
        std::vector<std::vector<int>> buckets(nums.size() + 1);
        for (const auto& pair : frequencyMap) {
            buckets[pair.second].push_back(pair.first);
        }

        // Get top k frequent elements
        std::vector<int> result;
        for (int i = buckets.size() - 1; i >= 0 && result.size() < k; i--) {
            for (int num : buckets[i]) {
                result.push_back(num);
                if (result.size() == k) break;
            }
        }

        return result;
    }
};

#endif // TOP_K_FREQUENT_HPP