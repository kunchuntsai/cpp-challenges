/*
 * 743. Network Delay Time (Medium)
 * https://leetcode.com/problems/network-delay-time/
 *
 * Problem:
 * You are given a network of n nodes, labeled from 1 to n. You are also given times, a list of travel times as directed edges times[i] = (u, v, w), where u is the source node, v is the target node, and w is the time it takes for a signal to travel from source to target.
 * Send a signal from a given node k. Return how long it takes for all the n nodes to receive the signal. If it is impossible, return -1.
 *
 * Example 1:
 * Input: times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
 * Output: 2
 *
 * Example 2:
 * Input: times = [[1,2,1]], n = 2, k = 1
 * Output: 1
 *
 * Constraints:
 * - 1 <= k <= n <= 100
 * - 1 <= times.length <= 6000
 * - times[i].length == 3
 * - 1 <= u, v <= n
 * - u != v
 * - 0 <= w <= 100
 */

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>

class NetworkDelayTime {
public:
    /**
     * Returns the time it takes for all nodes to receive the signal from node k using Dijkstra's algorithm.
     *
     * Time Complexity: O(E + N log N)
     * Space Complexity: O(N + E)
     *   where N = number of nodes, E = number of edges
     */
    static int solve(const std::vector<std::vector<int>>& times, int n, int k) {
        std::vector<std::vector<std::pair<int, int>>> graph(n + 1);
        for (const auto& edge : times) {
            graph[edge[0]].emplace_back(edge[1], edge[2]);
        }
        std::vector<int> dist(n + 1, INT_MAX);
        dist[k] = 0;
        using pii = std::pair<int, int>;
        std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
        pq.emplace(0, k);
        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d > dist[u]) continue;
            for (const auto& [v, w] : graph[u]) {
                if (dist[v] > d + w) {
                    dist[v] = d + w;
                    pq.emplace(dist[v], v);
                }
            }
        }
        int max_time = 0;
        for (int i = 1; i <= n; ++i) {
            if (dist[i] == INT_MAX) return -1;
            max_time = std::max(max_time, dist[i]);
        }
        return max_time;
    }
};

void test_network_delay_time() {
    struct TestCase {
        std::vector<std::vector<int>> times;
        int n, k, expected;
    };
    std::vector<TestCase> tests = {
        {{{2,1,1},{2,3,1},{3,4,1}}, 4, 2, 2},
        {{{1,2,1}}, 2, 1, 1},
        {{{1,2,1}}, 2, 2, -1}
    };
    for (const auto& test : tests) {
        std::cout << "Input: times = [";
        for (size_t i = 0; i < test.times.size(); ++i) {
            std::cout << "[" << test.times[i][0] << "," << test.times[i][1] << "," << test.times[i][2] << "]";
            if (i < test.times.size() - 1) std::cout << ", ";
        }
        std::cout << "], n = " << test.n << ", k = " << test.k << std::endl;
        int result = NetworkDelayTime::solve(test.times, test.n, test.k);
        std::cout << "Output: " << result << std::endl;
        std::cout << "Expected: " << test.expected << std::endl;
        std::cout << ((result == test.expected) ? "PASS" : "FAIL") << "\n";
    }
}

int main() {
    test_network_delay_time();
    return 0;
}