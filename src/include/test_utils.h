#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <iostream>
#include <vector>

inline void print_result(const std::vector<int>& result) {
    if (result.empty()) {
        std::cout << "No solution found" << std::endl;
    } else {
        std::cout << "Indices: [" << result[0] << ", " << result[1] << "]" << std::endl;
    }
}

#endif // TEST_UTILS_H