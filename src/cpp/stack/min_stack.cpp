/*
 * 155. Min Stack (Medium)
 * https://leetcode.com/problems/min-stack/
 *
 * Problem:
 * Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.
 *
 * Implement the MinStack class:
 *   - MinStack() initializes the stack object.
 *   - void push(int val) pushes the element val onto the stack.
 *   - void pop() removes the element on the top of the stack.
 *   - int top() gets the top element of the stack.
 *   - int getMin() retrieves the minimum element in the stack.
 *
 * Example 1:
 * Input: ["MinStack","push","push","push","getMin","pop","top","getMin"]
 *        [[],[-2],[0],[-3],[],[],[],[]]
 * Output: [null,null,null,null,-3,null,0,-2]
 *
 * Constraints:
 * - -2^31 <= val <= 2^31 - 1
 * - Methods pop, top and getMin operations will always be called on non-empty stacks.
 * - At most 3 * 10^4 calls will be made to push, pop, top, and getMin.
 */

#include <stack>
#include <iostream>
#include <limits>

class MinStack {
    std::stack<int> stk, min_stk;
public:
    /**
     * Initializes the MinStack object.
     *
     * Time Complexity: O(1) per operation
     * Space Complexity: O(n)
     */
    MinStack() {}

    void push(int val) {
        stk.push(val);
        if (min_stk.empty() || val <= min_stk.top()) min_stk.push(val);
    }

    void pop() {
        if (stk.top() == min_stk.top()) min_stk.pop();
        stk.pop();
    }

    int top() {
        return stk.top();
    }

    int getMin() {
        return min_stk.top();
    }
};

void test_min_stack() {
    MinStack minStack;
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    std::cout << "Test 1: getMin() => " << minStack.getMin() << " (Expected: -3)\n";
    minStack.pop();
    std::cout << "Test 2: top() => " << minStack.top() << " (Expected: 0)\n";
    std::cout << "Test 3: getMin() => " << minStack.getMin() << " (Expected: -2)\n";
}

int main() {
    test_min_stack();
    return 0;
} 