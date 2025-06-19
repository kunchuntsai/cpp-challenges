/*
 * 104. Maximum Depth of Binary Tree (Easy)
 * https://leetcode.com/problems/maximum-depth-of-binary-tree/
 *
 * Problem:
 * Given the root of a binary tree, return its maximum depth.
 *
 * Example 1:
 * Input: root = [3,9,20,null,null,15,7]
 * Output: 3
 *
 * Example 2:
 * Input: root = [1,null,2]
 * Output: 2
 *
 * Constraints:
 * - The number of nodes in the tree is in the range [0, 10^4].
 * - -100 <= Node.val <= 100
 */

#include <iostream>
#include <vector>
#include <queue>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class MaxDepthTree {
public:
    /**
     * Returns the maximum depth of a binary tree.
     *
     * @param root Pointer to the root of the tree
     * @return Maximum depth
     *
     * Time Complexity: O(n)
     * Space Complexity: O(h) (h = height of tree)
     */
    static int solve(TreeNode* root) {
        if (!root) return 0;
        return 1 + std::max(solve(root->left), solve(root->right));
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

void test_max_depth_tree() {
    TreeNode* t1 = build_tree({3,9,20,-9999,-9999,15,7});
    std::cout << "Test 1: [3,9,20,null,null,15,7] => " << MaxDepthTree::solve(t1) << " (Expected: 3)\n";
    TreeNode* t2 = build_tree({1,-9999,2});
    std::cout << "Test 2: [1,null,2] => " << MaxDepthTree::solve(t2) << " (Expected: 2)\n";
    TreeNode* t3 = build_tree({});
    std::cout << "Test 3: [] => " << MaxDepthTree::solve(t3) << " (Expected: 0)\n";
}

int main() {
    test_max_depth_tree();
    return 0;
} 