/*
 * 141. Linked List Cycle (Easy)
 * https://leetcode.com/problems/linked-list-cycle/
 *
 * Problem:
 * Given head, the head of a linked list, determine if the linked list has a cycle in it.
 *
 * Example 1:
 * Input: head = [3,2,0,-4], pos = 1 (tail connects to node index 1)
 * Output: true
 *
 * Example 2:
 * Input: head = [1,2], pos = 0
 * Output: true
 *
 * Example 3:
 * Input: head = [1], pos = -1
 * Output: false
 *
 * Constraints:
 * - The number of nodes in the list is in the range [0, 10^4].
 * - -10^5 <= Node.val <= 10^5
 * - pos is -1 or a valid index in the list.
 */

#include <iostream>
#include <vector>
#include <unordered_set>

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class LinkedListCycle {
public:
    /**
     * Detects if a linked list has a cycle using Floyd's Tortoise and Hare algorithm.
     *
     * @param head Pointer to the head of the list
     * @return True if there is a cycle, false otherwise
     *
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    static bool solve(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) return true;
        }
        return false;
    }
};

ListNode* build_list(const std::vector<int>& vals, int pos) {
    ListNode dummy(0);
    ListNode* curr = &dummy;
    std::vector<ListNode*> nodes;
    for (int v : vals) {
        curr->next = new ListNode(v);
        curr = curr->next;
        nodes.push_back(curr);
    }
    if (pos != -1 && !nodes.empty()) {
        curr->next = nodes[pos];
    }
    return dummy.next;
}

void test_linked_list_cycle() {
    ListNode* l1 = build_list({3,2,0,-4}, 1);
    std::cout << "Test 1: [3,2,0,-4], pos=1 => " << (LinkedListCycle::solve(l1) ? "true" : "false") << " (Expected: true)\n";
    ListNode* l2 = build_list({1,2}, 0);
    std::cout << "Test 2: [1,2], pos=0 => " << (LinkedListCycle::solve(l2) ? "true" : "false") << " (Expected: true)\n";
    ListNode* l3 = build_list({1}, -1);
    std::cout << "Test 3: [1], pos=-1 => " << (LinkedListCycle::solve(l3) ? "true" : "false") << " (Expected: false)\n";
}

int main() {
    test_linked_list_cycle();
    return 0;
} 