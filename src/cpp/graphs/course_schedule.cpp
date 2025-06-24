/*
 * 207. Course Schedule (Medium)
 * https://leetcode.com/problems/course-schedule/
 *
 * Problem:
 * There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. Prerequisites are given as pairs [a, b] meaning to take course a you must first take course b. Return true if you can finish all courses.
 *
 * Example 1:
 * Input: numCourses = 2, prerequisites = [[1,0]]
 * Output: true
 *
 * Example 2:
 * Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
 * Output: false
 *
 * Constraints:
 * - 1 <= numCourses <= 2000
 * - 0 <= prerequisites.length <= 5000
 * - prerequisites[i].length == 2
 * - 0 <= ai, bi < numCourses
 * - All the pairs are unique.
 */

#include <vector>
#include <queue>
#include <iostream>

class CourseSchedule {
public:
    /**
     * Determines if all courses can be finished.
     *
     * @param numCourses Number of courses
     * @param prerequisites List of prerequisite pairs
     * @return True if possible, false otherwise
     *
     * Time Complexity: O(V + E)
     * Space Complexity: O(V + E)
     */
    static bool solve(int numCourses, const std::vector<std::vector<int>>& prerequisites) {
        std::vector<std::vector<int>> graph(numCourses);
        std::vector<int> indegree(numCourses, 0);
        for (const auto& p : prerequisites) {
            graph[p[1]].push_back(p[0]);
            indegree[p[0]]++;
        }
        std::queue<int> q;
        for (int i = 0; i < numCourses; ++i) if (indegree[i] == 0) q.push(i);
        int count = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            ++count;
            for (int v : graph[u]) {
                if (--indegree[v] == 0) q.push(v);
            }
        }
        return count == numCourses;
    }
};

void test_course_schedule() {
    std::vector<std::vector<int>> p1 = {{1,0}};
    std::cout << "Test 1: numCourses=2, prerequisites=[[1,0]] => " << (CourseSchedule::solve(2, p1) ? "true" : "false") << " (Expected: true)\n";
    std::vector<std::vector<int>> p2 = {{1,0},{0,1}};
    std::cout << "Test 2: numCourses=2, prerequisites=[[1,0],[0,1]] => " << (CourseSchedule::solve(2, p2) ? "true" : "false") << " (Expected: false)\n";
}

int main() {
    test_course_schedule();
    return 0;
}