/*
 * 21. Merge Two Sorted Lists (Easy)
 * https://leetcode.com/problems/merge-two-sorted-lists/
 *
 * Problem:
 * Merge two sorted linked lists and return it as a new sorted list. The new list should be made by splicing together the nodes of the first two lists.
 *
 * Example 1:
 * Input: l1 = [1,2,4], l2 = [1,3,4]
 * Output: [1,1,2,3,4,4]
 *
 * Example 2:
 * Input: l1 = [], l2 = []
 * Output: []
 *
 * Example 3:
 * Input: l1 = [], l2 = [0]
 * Output: [0]
 *
 * Constraints:
 * - The number of nodes in both lists is in the range [0, 50].
 * - -100 <= Node.val <= 100
 */

#include <iostream>
#include <vector>

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class MergeSortedLists {
public:
    /**
     * Merges two sorted linked lists.
     *
     * @param l1 Pointer to the head of the first list
     * @param l2 Pointer to the head of the second list
     * @return Pointer to the head of the merged sorted list
     *
     * Time Complexity: O(n + m)
     * Space Complexity: O(1)
     */
    static ListNode* solve(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* curr = &dummy;
        while (l1 && l2) {
            if (l1->val < l2->val) {
                curr->next = l1;
                l1 = l1->next;
            } else {
                curr->next = l2;
                l2 = l2->next;
            }
            curr = curr->next;
        }
        curr->next = l1 ? l1 : l2;
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

void test_merge_sorted_lists() {
    ListNode* l1 = build_list({1,2,4});
    ListNode* l2 = build_list({1,3,4});
    std::cout << "Test 1: [1,2,4] + [1,3,4] => ";
    print_list(MergeSortedLists::solve(l1, l2));
    std::cout << "(Expected: [1,1,2,3,4,4])\n";
    ListNode* l3 = build_list({});
    ListNode* l4 = build_list({});
    std::cout << "Test 2: [] + [] => ";
    print_list(MergeSortedLists::solve(l3, l4));
    std::cout << "(Expected: [])\n";
    ListNode* l5 = build_list({});
    ListNode* l6 = build_list({0});
    std::cout << "Test 3: [] + [0] => ";
    print_list(MergeSortedLists::solve(l5, l6));
    std::cout << "(Expected: [0])\n";
}

int main() {
    test_merge_sorted_lists();
    return 0;
} 