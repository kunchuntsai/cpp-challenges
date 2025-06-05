# RAII-like Patterns in C

This document outlines various patterns for implementing RAII (Resource Acquisition Is Initialization) -like behavior in C programming. While C doesn't have built-in RAII support like C++, we can implement similar patterns to ensure proper resource management.

## Overview

RAII is a programming idiom where resource acquisition and release are bound to object lifetime. In C, we can implement similar patterns using various techniques to ensure proper resource cleanup.

## Key Patterns

### 1. Clear Ownership Transfer

This pattern explicitly defines ownership of resources and their transfer between functions.

```c
typedef struct {
    char* data;
    size_t size;
    int owner_id;  // For debugging ownership
} DataBuffer;

// Creator owns the buffer
DataBuffer* create_buffer(const char* initial_data, int owner_id);

// Function that borrows data (doesn't own it)
int process_data_borrow(const DataBuffer* buf);

// Function that takes ownership (caller gives up ownership)
int process_data_take_ownership(DataBuffer* buf);

// Function that returns ownership to caller
DataBuffer* process_data_return_ownership(DataBuffer* buf, int new_owner_id);
```

**Key Points:**
- Clear naming conventions indicate ownership transfer
- Documentation of ownership rules
- Explicit cleanup responsibilities

### 2. Reference Counting

This pattern allows multiple owners of a resource with automatic cleanup when the last reference is released.

```c
typedef struct {
    char* data;
    size_t size;
    int ref_count;
    pthread_mutex_t mutex;
} RefCountedBuffer;

RefCountedBuffer* refbuf_create(const char* data);
RefCountedBuffer* refbuf_retain(RefCountedBuffer* buf);
void refbuf_release(RefCountedBuffer* buf);
```

**Key Points:**
- Thread-safe reference counting
- Automatic cleanup on last release
- Safe sharing between threads

### 3. Thread-Safe Queue with Ownership

This pattern implements a producer-consumer queue with clear ownership transfer points.

```c
typedef struct {
    QueueNode* head;
    QueueNode* tail;
    pthread_mutex_t mutex;
    pthread_cond_t not_empty;
    int shutdown;
} ThreadSafeQueue;

ThreadSafeQueue* queue_create();
int queue_push(ThreadSafeQueue* q, void* data);  // Transfers ownership
void* queue_pop(ThreadSafeQueue* q);  // Receives ownership
void queue_destroy(ThreadSafeQueue* q);
```

**Key Points:**
- Clear ownership transfer points
- Thread-safe operations
- Proper cleanup on shutdown

### 4. Thread Pool with Data Processing

This pattern implements a thread pool where work items carry their own cleanup functions.

```c
typedef struct {
    void* data;
    void (*process_func)(void*);
    void (*cleanup_func)(void*);
} WorkItem;

ThreadPool* threadpool_create(int num_threads);
int threadpool_submit(ThreadPool* pool, void* data, 
                     void (*process_func)(void*),
                     void (*cleanup_func)(void*));
void threadpool_destroy(ThreadPool* pool);
```

**Key Points:**
- Work items carry their own cleanup functions
- Each thread processes and cleans up independently
- Pool manages thread lifecycle

### 5. Shared Memory with Copy Semantics

This pattern implements shared memory access with copy-on-read semantics.

```c
typedef struct {
    char* data;
    size_t size;
    pthread_rwlock_t rwlock;
} SharedBuffer;

SharedBuffer* shared_buffer_create(const char* initial_data);
char* shared_buffer_read_copy(SharedBuffer* buf);  // Caller owns the copy
int shared_buffer_write(SharedBuffer* buf, const char* new_data);
void shared_buffer_destroy(SharedBuffer* buf);
```

**Key Points:**
- Each thread gets its own copy
- No shared mutable state
- Simple but memory-intensive

## Best Practices

1. **Clear Ownership Rules**
   - Document who owns what
   - Use naming conventions (borrow_, take_, return_)
   - Transfer ownership explicitly

2. **Error Handling**
   - Check all allocation failures
   - Clean up resources on error
   - Use consistent error handling patterns

3. **Thread Safety**
   - Use appropriate synchronization primitives
   - Document thread safety guarantees
   - Handle cleanup in thread-safe manner

4. **Resource Management**
   - Pair resource acquisition with cleanup
   - Use consistent cleanup patterns
   - Handle cleanup in all code paths

## Implementation Tips

1. **Initialization**
   - Initialize all resources in creation functions
   - Check for initialization failures
   - Clean up partially initialized resources

2. **Cleanup**
   - Implement cleanup functions for all resources
   - Handle cleanup in reverse order of acquisition
   - Make cleanup functions idempotent

3. **Error Handling**
   - Use goto for centralized cleanup
   - Check all error conditions
   - Clean up resources on all error paths

## Example Usage

```c
void example_usage() {
    // Create and use a reference-counted buffer
    RefCountedBuffer* buf = refbuf_create("Shared Data");
    if (!buf) return;
    
    // Start multiple threads that use the buffer
    pthread_t threads[3];
    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, ref_counting_thread, buf);
    }
    
    // Wait for threads to complete
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // Release original reference
    refbuf_release(buf);
}
```

## Common Pitfalls

1. **Ownership Confusion**
   - Unclear ownership transfer
   - Multiple owners without reference counting
   - Missing cleanup calls

2. **Thread Safety Issues**
   - Unsafe resource sharing
   - Race conditions in cleanup
   - Deadlocks in synchronization

3. **Resource Leaks**
   - Missing cleanup in error paths
   - Forgotten resources
   - Incomplete cleanup

## Tools and Debugging

1. **Valgrind**
   - Use for memory leak detection
   - Command: `valgrind --leak-check=full ./your_program`

2. **Thread Sanitizer**
   - Compile with: `-fsanitize=thread`
   - Detects thread safety issues

3. **Static Analysis**
   - Clang Static Analyzer
   - Coverity
   - PVS-Studio

## Additional Resources

1. [C Memory Management](https://en.wikipedia.org/wiki/C_dynamic_memory_allocation)
2. [POSIX Threads Programming](https://computing.llnl.gov/tutorials/pthreads/)
3. [Thread Sanitizer](https://clang.llvm.org/docs/ThreadSanitizer.html) 