/*
 * 206. Reverse Linked List (Easy)
 * https://leetcode.com/problems/reverse-linked-list/
 *
 * Problem:
 * Given the head of a singly linked list, reverse the list, and return the reversed list.
 *
 * Example 1:
 * Input: head = [1,2,3,4,5]
 * Output: [5,4,3,2,1]
 *
 * Example 2:
 * Input: head = [1,2]
 * Output: [2,1]
 *
 * Example 3:
 * Input: head = []
 * Output: []
 *
 * Constraints:
 * - The number of nodes in the list is the range [0, 5000].
 * - -5000 <= Node.val <= 5000
 */

#include <iostream>
#include <vector>

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class ReverseLinkedList {
public:
    /**
     * Reverses a singly linked list.
     *
     * @param head Pointer to the head of the list
     * @return Pointer to the new head of the reversed list
     *
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    static ListNode* solve(ListNode* head) {
        ListNode* prev = nullptr;
        while (head) {
            ListNode* next = head->next;
            head->next = prev;
            prev = head;
            head = next;
        }
        return prev;
    }
};

void print_list(ListNode* head) {
    std::cout << "[";
    while (head) {
        std::cout << head->val;
        if (head->next) std::cout << ",";
        head = head->next;
    }
    std::cout << "]\n";
}

ListNode* build_list(const std::vector<int>& vals) {
    ListNode dummy(0);
    ListNode* curr = &dummy;
    for (int v : vals) {
        curr->next = new ListNode(v);
        curr = curr->next;
    }
    return dummy.next;
}

void test_reverse_linked_list() {
    ListNode* l1 = build_list({1,2,3,4,5});
    std::cout << "Test 1: [1,2,3,4,5] => ";
    print_list(ReverseLinkedList::solve(l1));
    std::cout << "(Expected: [5,4,3,2,1])\n";
    ListNode* l2 = build_list({1,2});
    std::cout << "Test 2: [1,2] => ";
    print_list(ReverseLinkedList::solve(l2));
    std::cout << "(Expected: [2,1])\n";
    ListNode* l3 = build_list({});
    std::cout << "Test 3: [] => ";
    print_list(ReverseLinkedList::solve(l3));
    std::cout << "(Expected: [])\n";
}

int main() {
    test_reverse_linked_list();
    return 0;
} 