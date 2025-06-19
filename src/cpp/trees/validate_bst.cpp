/*
 * 98. Validate Binary Search Tree (Medium)
 * https://leetcode.com/problems/validate-binary-search-tree/
 *
 * Problem:
 * Given the root of a binary tree, determine if it is a valid binary search tree (BST).
 *
 * Example 1:
 * Input: root = [2,1,3]
 * Output: true
 *
 * Example 2:
 * Input: root = [5,1,4,null,null,3,6]
 * Output: false
 *
 * Constraints:
 * - The number of nodes in the tree is in the range [1, 10^4].
 * - -2^31 <= Node.val <= 2^31 - 1
 */

#include <iostream>
#include <vector>
#include <limits>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class ValidateBST {
public:
    /**
     * Determines if a binary tree is a valid BST.
     *
     * @param root Pointer to the root of the tree
     * @return True if valid BST, false otherwise
     *
     * Time Complexity: O(n)
     * Space Complexity: O(h) (h = height of tree)
     */
    static bool solve(TreeNode* root) {
        return helper(root, std::numeric_limits<long long>::min(), std::numeric_limits<long long>::max());
    }
private:
    static bool helper(TreeNode* node, long long minVal, long long maxVal) {
        if (!node) return true;
        if (node->val <= minVal || node->val >= maxVal) return false;
        return helper(node->left, minVal, node->val) && helper(node->right, node->val, maxVal);
    }
};

TreeNode* build_tree(const std::vector<int>& vals) {
    if (vals.empty()) return nullptr;
    std::vector<TreeNode*> nodes;
    for (int v : vals) nodes.push_back(v == -9999 ? nullptr : new TreeNode(v));
    int j = 1;
    for (int i = 0; i < nodes.size() && j < nodes.size(); ++i) {
        if (nodes[i]) {
            if (j < nodes.size()) nodes[i]->left = nodes[j++];
            if (j < nodes.size()) nodes[i]->right = nodes[j++];
        }
    }
    return nodes[0];
}

void test_validate_bst() {
    TreeNode* t1 = build_tree({2,1,3});
    std::cout << "Test 1: [2,1,3] => " << (ValidateBST::solve(t1) ? "true" : "false") << " (Expected: true)\n";
    TreeNode* t2 = build_tree({5,1,4,-9999,-9999,3,6});
    std::cout << "Test 2: [5,1,4,null,null,3,6] => " << (ValidateBST::solve(t2) ? "true" : "false") << " (Expected: false)\n";
}

int main() {
    test_validate_bst();
    return 0;
} 