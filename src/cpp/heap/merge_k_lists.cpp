/*
 * 23. Merge k Sorted Lists (Hard)
 * https://leetcode.com/problems/merge-k-sorted-lists/
 *
 * Problem:
 * Merge k sorted linked lists and return it as one sorted list.
 *
 * Example 1:
 * Input: lists = [[1,4,5],[1,3,4],[2,6]]
 * Output: [1,1,2,3,4,4,5,6]
 *
 * Example 2:
 * Input: lists = []
 * Output: []
 *
 * Example 3:
 * Input: lists = [[]]
 * Output: []
 *
 * Constraints:
 * - k == lists.length
 * - 0 <= k <= 10^4
 * - 0 <= lists[i].length <= 500
 * - -10^4 <= lists[i][j] <= 10^4
 */

#include <vector>
#include <queue>
#include <iostream>

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class MergeKLists {
public:
    /**
     * Merges k sorted linked lists.
     *
     * @param lists Vector of ListNode pointers
     * @return Pointer to the head of the merged sorted list
     *
     * Time Complexity: O(N log k), where N is the total number of nodes
     * Space Complexity: O(k)
     */
    static ListNode* solve(std::vector<ListNode*>& lists) {
        auto cmp = [](ListNode* a, ListNode* b) { return a->val > b->val; };
        std::priority_queue<ListNode*, std::vector<ListNode*>, decltype(cmp)> pq(cmp);
        for (auto node : lists) if (node) pq.push(node);
        ListNode dummy(0), *tail = &dummy;
        while (!pq.empty()) {
            ListNode* node = pq.top(); pq.pop();
            tail->next = node;
            tail = tail->next;
            if (node->next) pq.push(node->next);
        }
        return dummy.next;
    }
};

ListNode* build_list(const std::vector<int>& vals) {
    ListNode dummy(0);
    ListNode* curr = &dummy;
    for (int v : vals) {
        curr->next = new ListNode(v);
        curr = curr->next;
    }
    return dummy.next;
}

void print_list(ListNode* head) {
    std::cout << "[";
    while (head) {
        std::cout << head->val;
        if (head->next) std::cout << ",";
        head = head->next;
    }
    std::cout << "]\n";
}

void test_merge_k_lists() {
    std::vector<ListNode*> lists1 = {build_list({1,4,5}), build_list({1,3,4}), build_list({2,6})};
    std::cout << "Test 1: [[1,4,5],[1,3,4],[2,6]] => ";
    print_list(MergeKLists::solve(lists1));
    std::cout << "(Expected: [1,1,2,3,4,4,5,6])\n";
    std::vector<ListNode*> lists2 = {};
    std::cout << "Test 2: [] => ";
    print_list(MergeKLists::solve(lists2));
    std::cout << "(Expected: [])\n";
    std::vector<ListNode*> lists3 = {build_list({})};
    std::cout << "Test 3: [[]] => ";
    print_list(MergeKLists::solve(lists3));
    std::cout << "(Expected: [])\n";
}

int main() {
    test_merge_k_lists();
    return 0;
}