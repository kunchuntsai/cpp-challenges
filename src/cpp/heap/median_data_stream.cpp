/*
 * 295. Find Median from Data Stream (Hard)
 * https://leetcode.com/problems/find-median-from-data-stream/
 *
 * Problem:
 * The MedianFinder class supports adding numbers and finding the median in O(log n) time per operation.
 *
 * Example 1:
 * Input: ["MedianFinder","addNum","addNum","findMedian"], [[],[1],[2],[]]
 * Output: [null,null,null,1.5]
 *
 * Example 2:
 * Input: ["MedianFinder","addNum","addNum","addNum","findMedian"], [[],[2],[3],[4],[]]
 * Output: [null,null,null,null,2.0]
 *
 * Constraints:
 * - -10^5 <= num <= 10^5
 * - There will be at least one element before calling findMedian.
 * - At most 5 * 10^4 calls will be made to addNum and findMedian.
 */

#include <queue>
#include <vector>
#include <iostream>

class MedianFinder {
    std::priority_queue<int> lo;
    std::priority_queue<int, std::vector<int>, std::greater<int>> hi;
public:
    /**
     * Initializes the MedianFinder object.
     *
     * Time Complexity: O(log n) per addNum, O(1) for findMedian
     * Space Complexity: O(n)
     */
    MedianFinder() {}

    void addNum(int num) {
        lo.push(num);
        hi.push(lo.top());
        lo.pop();
        if (lo.size() < hi.size()) {
            lo.push(hi.top());
            hi.pop();
        }
    }

    double findMedian() {
        if (lo.size() > hi.size()) return lo.top();
        return (lo.top() + hi.top()) / 2.0;
    }
};

void test_median_data_stream() {
    MedianFinder mf;
    mf.addNum(1);
    mf.addNum(2);
    std::cout << "Test 1: [1,2] => " << mf.findMedian() << " (Expected: 1.5)\n";
    mf.addNum(3);
    std::cout << "Test 2: [1,2,3] => " << mf.findMedian() << " (Expected: 2.0)\n";
}

int main() {
    test_median_data_stream();
    return 0;
}