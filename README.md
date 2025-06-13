# C++ Challenges
This order allows for a gradual increase in difficulty, testing various aspects of C++ programming along the way. It starts with basic data structures and algorithms, progresses through memory management and design patterns, and culminates in advanced concurrency and system-level programming.

Keep in mind that the perceived difficulty can vary based on individual experience. For example, someone with strong concurrency experience might find the Thread Pool easier than the JSON Parser.

* [Circular Buffer](src/include/ring_buffer.h): This is a relatively straightforward data structure implementation, making it a good starting point.
* [Trie (Prefix Tree)](src/include/trie.h): While it involves tree structures, the concept and implementation are generally straightforward.
* LRU Cache: This requires understanding of data structures and basic algorithms, but is still relatively manageable.
* [Simple Smart Pointer](src/include/smart_ptr.h): This introduces memory management and some modern C++ concepts, increasing the difficulty slightly.
* [Thread-Safe Singleton Logger](src/include/logger.h): This brings in basic concurrency and design patterns, stepping up the complexity.
* Generic Observable Pattern: This challenge tests understanding of templates and design patterns, which can be tricky.
* Thread-Safe Queue: This further tests concurrency knowledge, focusing on synchronization primitives.
* JSON Parser: Parsing involves more complex string manipulation and recursive logic, increasing the difficulty.
* Memory Pool Allocator: This requires deep understanding of memory management and low-level optimizations.
* [Thread Pool](src/include/thread_pool.h): This is the most complex, combining advanced concurrency, templates, and careful resource management.

## Build and Run
The project uses CMake for building and includes convenient scripts for building and running:

```bash
# Build the project
./scripts/build.sh

# Build with debug flags
./scripts/build.sh -d

# Clean build directory and rebuild
./scripts/build.sh -c

# Run the first available program
./scripts/run.sh

# List all available programs
./scripts/run.sh -l

# Run a specific program
./scripts/run.sh program_name
```


# C Practices
This section contains focused C programming exercises organized into key practice areas to help improve C programming skills. The exercises are located in `src/c/` and cover fundamental C concepts.

## Structure
- `memory/` - Pointer manipulation and memory management
- `strings/` - String processing and manipulation
- `arrays/` - Array and buffer operations
- `bits/` - Bit manipulation techniques
- `system/` - Low-level system concepts

## How to Build and Run
The C practice section uses dedicated build and run scripts:

```bash
# Build all C programs
./scripts/build_c.sh

# Build a specific program
./scripts/build_c.sh -t src/c/memory/pointer_demo

# Run all programs
./scripts/run_c.sh -a

# Run a specific program
./scripts/run_c.sh pointer_demo

# List all available programs
./scripts/run_c.sh -l
```

For more detailed information about the C practices, please refer to the [C Practice README](src/c/README.md).

# Leetcode Practices
This section contains solutions to Leetcode problems, organized by categories. The solutions are located in `src/cpp/` and include test cases for each problem.

## Structure
- `arrays_hashing/` - Array and hash table based problems
  - Two Sum
  - Top K Frequent Elements
  - Group Anagrams

## How to Build and Run
The Leetcode practice section uses the same build system as the main project:

```bash
# Build all Leetcode solutions
./scripts/build.sh

# Build with debug flags
./scripts/build.sh -d

# Clean build directory and rebuild
./scripts/build.sh -c

# List all available test programs
./scripts/run.sh -l

# Run a specific test
./scripts/run.sh two_sum_test
./scripts/run.sh top_k_frequent_test
./scripts/run.sh group_anagrams_test
```

Each test program includes multiple test cases to verify the correctness of the solution. The output will show the test cases and their results.

For more detailed information about the C practices, please refer to the [Cpp Practice README](src/cpp/README.md).