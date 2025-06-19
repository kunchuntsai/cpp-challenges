/*
 * 226. Invert Binary Tree (Easy)
 * https://leetcode.com/problems/invert-binary-tree/
 *
 * Problem:
 * Given the root of a binary tree, invert the tree, and return its root.
 *
 * Example 1:
 * Input: root = [4,2,7,1,3,6,9]
 * Output: [4,7,2,9,6,3,1]
 *
 * Example 2:
 * Input: root = [2,1,3]
 * Output: [2,3,1]
 *
 * Example 3:
 * Input: root = []
 * Output: []
 *
 * Constraints:
 * - The number of nodes in the tree is in the range [0, 100].
 * - -100 <= Node.val <= 100
 */

#include <iostream>
#include <queue>
#include <vector>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class InvertTree {
public:
    /**
     * Inverts a binary tree.
     *
     * @param root Pointer to the root of the tree
     * @return Pointer to the root of the inverted tree
     *
     * Time Complexity: O(n)
     * Space Complexity: O(h) (h = height of tree)
     */
    static TreeNode* solve(TreeNode* root) {
        if (!root) return nullptr;
        TreeNode* left = solve(root->left);
        TreeNode* right = solve(root->right);
        root->left = right;
        root->right = left;
        return root;
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

void print_level_order(TreeNode* root) {
    std::queue<TreeNode*> q;
    q.push(root);
    std::cout << "[";
    bool first = true;
    while (!q.empty()) {
        TreeNode* node = q.front(); q.pop();
        if (!first) std::cout << ",";
        first = false;
        if (node) {
            std::cout << node->val;
            q.push(node->left);
            q.push(node->right);
        } else {
            std::cout << "null";
        }
    }
    std::cout << "]\n";
}

void test_invert_tree() {
    TreeNode* t1 = build_tree({4,2,7,1,3,6,9});
    std::cout << "Test 1: [4,2,7,1,3,6,9] => ";
    print_level_order(InvertTree::solve(t1));
    std::cout << "(Expected: [4,7,2,9,6,3,1])\n";
    TreeNode* t2 = build_tree({2,1,3});
    std::cout << "Test 2: [2,1,3] => ";
    print_level_order(InvertTree::solve(t2));
    std::cout << "(Expected: [2,3,1])\n";
    TreeNode* t3 = build_tree({});
    std::cout << "Test 3: [] => ";
    print_level_order(InvertTree::solve(t3));
    std::cout << "(Expected: [])\n";
}

int main() {
    test_invert_tree();
    return 0;
} 