/*
 * 133. Clone Graph (Medium)
 * https://leetcode.com/problems/clone-graph/
 *
 * Problem:
 * Given a reference of a node in a connected undirected graph, return a deep copy (clone) of the graph.
 *
 * Example 1:
 * Input: adjList = [[2,4],[1,3],[2,4],[1,3]]
 * Output: [[2,4],[1,3],[2,4],[1,3]]
 *
 * Example 2:
 * Input: adjList = [[]]
 * Output: [[]]
 *
 * Example 3:
 * Input: adjList = []
 * Output: []
 *
 * Constraints:
 * - The number of nodes in the graph is in the range [0, 100].
 * - 1 <= Node.val <= 100
 * - Node.val is unique for each node.
 * - There are no repeated edges and no self-loops in the graph.
 */

#include <vector>
#include <unordered_map>
#include <queue>
#include <iostream>

struct Node {
    int val;
    std::vector<Node*> neighbors;
    Node(int _val) : val(_val) {}
};

class CloneGraph {
public:
    /**
     * Clones an undirected graph.
     *
     * @param node Pointer to a node in the graph
     * @return Pointer to the cloned node
     *
     * Time Complexity: O(N)
     * Space Complexity: O(N)
     */
    static Node* solve(Node* node) {
        if (!node) return nullptr;
        std::unordered_map<Node*, Node*> mp;
        std::queue<Node*> q;
        q.push(node);
        mp[node] = new Node(node->val);
        while (!q.empty()) {
            Node* curr = q.front(); q.pop();
            for (Node* nei : curr->neighbors) {
                if (!mp.count(nei)) {
                    mp[nei] = new Node(nei->val);
                    q.push(nei);
                }
                mp[curr]->neighbors.push_back(mp[nei]);
            }
        }
        return mp[node];
    }
};

// No simple test for graph structure, but you can build and clone graphs here.
int main() {
    // Example: build a simple graph and clone it
    Node* n1 = new Node(1);
    Node* n2 = new Node(2);
    Node* n3 = new Node(3);
    Node* n4 = new Node(4);
    n1->neighbors = {n2, n4};
    n2->neighbors = {n1, n3};
    n3->neighbors = {n2, n4};
    n4->neighbors = {n1, n3};
    Node* clone = CloneGraph::solve(n1);
    std::cout << "Graph cloned.\n";
    return 0;
}