#include <iostream>
#include "ring_buffer.h"
#include "trie.h"
#include "logger.h"
#include "unit_test.h"

// Declare test functions
void runTrieTests();
void runRingBufferTests();
void runLoggerTests();

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