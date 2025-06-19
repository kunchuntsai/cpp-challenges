/*
 * 39. Combination Sum (Medium)
 * https://leetcode.com/problems/combination-sum/
 *
 * Problem:
 * Given an array of distinct integers candidates and a target integer target, return a list of all unique combinations of candidates where the chosen numbers sum to target. You may return the combinations in any order.
 *
 * Example 1:
 * Input: candidates = [2,3,6,7], target = 7
 * Output: [[2,2,3],[7]]
 *
 * Example 2:
 * Input: candidates = [2,3,5], target = 8
 * Output: [[2,2,2,2],[2,3,3],[3,5]]
 *
 * Example 3:
 * Input: candidates = [2], target = 1
 * Output: []
 *
 * Constraints:
 * - 1 <= candidates.length <= 30
 * - 2 <= candidates[i] <= 40
 * - All elements of candidates are distinct.
 * - 1 <= target <= 40
 */

#include <vector>
#include <iostream>

class CombinationSum {
public:
    /**
     * Returns all unique combinations that sum to target.
     *
     * @param candidates Vector of distinct integers
     * @param target Target sum
     * @return Vector of combinations
     *
     * Time Complexity: O(2^t), where t = target
     * Space Complexity: O(2^t)
     */
    static std::vector<std::vector<int>> solve(const std::vector<int>& candidates, int target) {
        std::vector<std::vector<int>> res;
        std::vector<int> curr;
        backtrack(candidates, target, 0, curr, res);
        return res;
    }
private:
    static void backtrack(const std::vector<int>& candidates, int target, int start, std::vector<int>& curr, std::vector<std::vector<int>>& res) {
        if (target == 0) {
            res.push_back(curr);
            return;
        }
        for (int i = start; i < candidates.size(); ++i) {
            if (candidates[i] > target) continue;
            curr.push_back(candidates[i]);
            backtrack(candidates, target - candidates[i], i, curr, res);
            curr.pop_back();
        }
    }
};

void print_result(const std::vector<std::vector<int>>& result) {
    std::cout << "[";
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << "[";
        for (size_t j = 0; j < result[i].size(); ++j) {
            std::cout << result[i][j];
            if (j < result[i].size() - 1) std::cout << ",";
        }
        std::cout << "]";
        if (i < result.size() - 1) std::cout << ",";
    }
    std::cout << "]\n";
}

void test_combination_sum() {
    std::vector<int> c1 = {2,3,6,7};
    std::cout << "Test 1: [2,3,6,7], target=7 => ";
    print_result(CombinationSum::solve(c1, 7));
    std::cout << "(Expected: [[2,2,3],[7]])\n";
    std::vector<int> c2 = {2,3,5};
    std::cout << "Test 2: [2,3,5], target=8 => ";
    print_result(CombinationSum::solve(c2, 8));
    std::cout << "(Expected: [[2,2,2,2],[2,3,3],[3,5]])\n";
    std::vector<int> c3 = {2};
    std::cout << "Test 3: [2], target=1 => ";
    print_result(CombinationSum::solve(c3, 1));
    std::cout << "(Expected: [])\n";
}

int main() {
    test_combination_sum();
    return 0;
} 