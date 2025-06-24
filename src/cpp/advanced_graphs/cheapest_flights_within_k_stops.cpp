/*
 * 787. Cheapest Flights Within K Stops (Medium)
 * https://leetcode.com/problems/cheapest-flights-within-k-stops/
 *
 * Problem:
 * There are n cities and m flights. You are given flights, where flights[i] = [fromi, toi, pricei], and two cities src and dst, and an integer k.
 * Return the cheapest price from src to dst with at most k stops. If there is no such route, return -1.
 *
 * Example 1:
 * Input: n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], src = 0, dst = 2, k = 1
 * Output: 200
 *
 * Example 2:
 * Input: n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], src = 0, dst = 2, k = 0
 * Output: 500
 *
 * Constraints:
 * - 1 <= n <= 100
 * - 0 <= flights.length <= (n * (n - 1) / 2)
 * - flights[i].length == 3
 * - 0 <= fromi, toi < n
 * - fromi != toi
 * - 1 <= pricei <= 10^4
 * - There will not be any multiple flights between two cities.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <climits>

class CheapestFlightsWithinKStops {
public:
    /**
     * Returns the cheapest price from src to dst with at most k stops using BFS/modified Dijkstra.
     *
     * Time Complexity: O(n^2 * k) in the worst case
     * Space Complexity: O(n^2)
     */
    static int solve(int n, const std::vector<std::vector<int>>& flights, int src, int dst, int k) {
        std::vector<std::vector<std::pair<int, int>>> graph(n);
        for (const auto& f : flights) {
            graph[f[0]].emplace_back(f[1], f[2]);
        }
        std::vector<int> dist(n, INT_MAX);
        dist[src] = 0;
        std::queue<std::pair<int, int>> q; // {city, cost}
        q.emplace(src, 0);
        int stops = 0;
        while (!q.empty() && stops <= k) {
            int sz = q.size();
            std::vector<int> temp = dist;
            for (int i = 0; i < sz; ++i) {
                auto [u, cost] = q.front(); q.pop();
                for (const auto& [v, w] : graph[u]) {
                    if (cost + w < temp[v]) {
                        temp[v] = cost + w;
                        q.emplace(v, temp[v]);
                    }
                }
            }
            dist = temp;
            ++stops;
        }
        return dist[dst] == INT_MAX ? -1 : dist[dst];
    }
};

void test_cheapest_flights_within_k_stops() {
    struct TestCase {
        int n;
        std::vector<std::vector<int>> flights;
        int src, dst, k, expected;
    };
    std::vector<TestCase> tests = {
        {3, {{0,1,100},{1,2,100},{0,2,500}}, 0, 2, 1, 200},
        {3, {{0,1,100},{1,2,100},{0,2,500}}, 0, 2, 0, 500},
        {4, {{0,1,1},{0,2,5},{1,2,1},{2,3,1}}, 0, 3, 1, 6},
        {2, {}, 0, 1, 1, -1}
    };
    for (const auto& test : tests) {
        std::cout << "Input: n = " << test.n << ", flights = [";
        for (size_t i = 0; i < test.flights.size(); ++i) {
            std::cout << "[" << test.flights[i][0] << "," << test.flights[i][1] << "," << test.flights[i][2] << "]";
            if (i < test.flights.size() - 1) std::cout << ", ";
        }
        std::cout << "], src = " << test.src << ", dst = " << test.dst << ", k = " << test.k << std::endl;
        int result = CheapestFlightsWithinKStops::solve(test.n, test.flights, test.src, test.dst, test.k);
        std::cout << "Output: " << result << std::endl;
        std::cout << "Expected: " << test.expected << std::endl;
        std::cout << ((result == test.expected) ? "PASS" : "FAIL") << "\n";
    }
}

int main() {
    test_cheapest_flights_within_k_stops();
    return 0;
}