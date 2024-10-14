#include <iostream>
#include "main.h"

int main() {
    std::cout << "Running all tests..." << std::endl;

    std::cout << "\nRunning Trie tests:" << std::endl;
    runTrieTests();

    std::cout << "\nRunning RingBuffer tests:" << std::endl;
    runRingBufferTests();

    std::cout << "\nRunning Logger tests:" << std::endl;
    runLoggerTests();

    return 0;
}