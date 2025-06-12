# C Threading and Memory Management Interview Solutions

This document provides comprehensive solutions to common C programming interview questions focusing on threading, synchronization, and memory management.

## Table of Contents

- [1. Debugging Exercise - Fix Race Condition](#1-debugging-exercise---fix-race-condition)
- [2. Conceptual Questions](#2-conceptual-questions)
- [3. Simplified Implementation - Thread-Safe Counter](#3-simplified-implementation---thread-safe-counter)
- [4. Memory Management Focus](#4-memory-management-focus)
- [Interview Tips](#interview-tips)

---

## 1. Debugging Exercise - Fix Race Condition

### Problem
```c
// "Fix the race condition"
void buggy_function() {
    static int counter = 0;
    counter++;  // Race condition!
    printf("%d\n", counter);
}
```

**Issue**: Multiple threads accessing and modifying the static `counter` variable without synchronization leads to race conditions.

### Solution 1: Using Mutex
```c
#include <pthread.h>

static pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

void fixed_function_v1() {
    static int counter = 0;

    pthread_mutex_lock(&counter_mutex);
    counter++;
    printf("%d\n", counter);
    pthread_mutex_unlock(&counter_mutex);
}
```

### Solution 2: Using Atomic Operations (C11)
```c
#include <stdatomic.h>

void fixed_function_v2() {
    static atomic_int counter = ATOMIC_VAR_INIT(0);

    int value = atomic_fetch_add(&counter, 1) + 1;
    printf("%d\n", value);
}
```

### Solution 3: Minimize Critical Section
```c
void fixed_function_v3() {
    static int counter = 0;
    int local_value;

    pthread_mutex_lock(&counter_mutex);
    counter++;
    local_value = counter;
    pthread_mutex_unlock(&counter_mutex);

    printf("%d\n", local_value);  // Print outside critical section
}
```

**Trade-offs:**
- **Mutex**: Simple, widely supported, but slower than atomics
- **Atomics**: Faster, lock-free, but requires C11 and more complex for non-trivial operations
- **Minimized critical section**: Reduces lock contention by moving I/O outside the lock

---

## 2. Conceptual Questions

### Q: "How would you make this data structure thread-safe?"

**Answer Approach:**
1. **Identify shared mutable state**
2. **Choose appropriate synchronization primitive:**
   - Mutex: For exclusive access
   - Read-write lock: For reader-heavy workloads
   - Atomic operations: For simple operations
   - Condition variables: For blocking/signaling
3. **Minimize critical sections**
4. **Consider lock-free alternatives**
5. **Handle error cases in synchronization**

**Example - Thread-Safe Linked List:**
```c
// Non-thread-safe version
typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} SimpleList;

// Thread-safe version
typedef struct {
    Node* head;
    pthread_mutex_t mutex;
} ThreadSafeList;

ThreadSafeList* list_create() {
    ThreadSafeList* list = malloc(sizeof(ThreadSafeList));
    if (!list) return NULL;

    list->head = NULL;
    if (pthread_mutex_init(&list->mutex, NULL) != 0) {
        free(list);
        return NULL;
    }
    return list;
}

int list_insert(ThreadSafeList* list, int data) {
    if (!list) return -1;

    Node* new_node = malloc(sizeof(Node));
    if (!new_node) return -1;

    new_node->data = data;

    pthread_mutex_lock(&list->mutex);
    new_node->next = list->head;
    list->head = new_node;
    pthread_mutex_unlock(&list->mutex);

    return 0;
}
```

### Q: "What's the difference between mutex and semaphore?"

**MUTEX (Mutual Exclusion):**
- Binary lock (locked/unlocked)
- Ownership concept - only the thread that locks can unlock
- Used for protecting critical sections
- Prevents race conditions

**SEMAPHORE:**
- Counter-based (can have value > 1)
- No ownership - any thread can signal
- Used for resource counting and signaling
- Types: Binary semaphore (like mutex) and Counting semaphore

**Use Cases:**
- **Mutex**: Protecting shared data structure
- **Semaphore**: Limiting number of concurrent connections

### Q: "Explain deadlock and how to prevent it"

**DEADLOCK** occurs when two or more threads are blocked forever, each waiting for the other to release a resource.

**Classic Example:**
```
Thread 1: Lock A -> Lock B
Thread 2: Lock B -> Lock A
```

**Prevention Strategies:**
1. **Lock Ordering**: Always acquire locks in same order
2. **Timeout**: Use timed lock operations
3. **Avoid Nested Locks**: Minimize holding multiple locks
4. **Lock Hierarchy**: Assign priorities to locks
5. **Deadlock Detection**: Monitor and break cycles

**Deadlock Example (DON'T DO THIS):**
```c
pthread_mutex_t mutex_a = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_b = PTHREAD_MUTEX_INITIALIZER;

void* thread1_deadlock(void* arg) {
    pthread_mutex_lock(&mutex_a);
    printf("Thread 1: Locked A\n");
    sleep(1);
    pthread_mutex_lock(&mutex_b);  // Will deadlock
    // ... rest of function
}

void* thread2_deadlock(void* arg) {
    pthread_mutex_lock(&mutex_b);
    printf("Thread 2: Locked B\n");
    sleep(1);
    pthread_mutex_lock(&mutex_a);  // Will deadlock
    // ... rest of function
}
```

**Fixed Version (Lock Ordering):**
```c
void* thread1_fixed(void* arg) {
    pthread_mutex_lock(&mutex_a);  // Always lock A first
    pthread_mutex_lock(&mutex_b);  // Then lock B
    // ... do work
    pthread_mutex_unlock(&mutex_b);
    pthread_mutex_unlock(&mutex_a);
}

void* thread2_fixed(void* arg) {
    pthread_mutex_lock(&mutex_a);  // Always lock A first
    pthread_mutex_lock(&mutex_b);  // Then lock B
    // ... do work
    pthread_mutex_unlock(&mutex_b);
    pthread_mutex_unlock(&mutex_a);
}
```

---

## 3. Simplified Implementation - Thread-Safe Counter

### Problem
```c
// "Implement a thread-safe counter"
typedef struct {
    int value;
    pthread_mutex_t mutex;
} SafeCounter;
```

### Complete Implementation
```c
#include <pthread.h>
#include <stdlib.h>

typedef struct {
    int value;
    pthread_mutex_t mutex;
} SafeCounter;

// Initialize counter
SafeCounter* counter_create(int initial_value) {
    SafeCounter* counter = malloc(sizeof(SafeCounter));
    if (!counter) return NULL;

    counter->value = initial_value;
    if (pthread_mutex_init(&counter->mutex, NULL) != 0) {
        free(counter);
        return NULL;
    }

    return counter;
}

// Increment counter and return new value
int counter_increment(SafeCounter* counter) {
    if (!counter) return -1;

    pthread_mutex_lock(&counter->mutex);
    counter->value++;
    int result = counter->value;
    pthread_mutex_unlock(&counter->mutex);

    return result;
}

// Decrement counter and return new value
int counter_decrement(SafeCounter* counter) {
    if (!counter) return -1;

    pthread_mutex_lock(&counter->mutex);
    counter->value--;
    int result = counter->value;
    pthread_mutex_unlock(&counter->mutex);

    return result;
}

// Get current value
int counter_get(SafeCounter* counter) {
    if (!counter) return -1;

    pthread_mutex_lock(&counter->mutex);
    int result = counter->value;
    pthread_mutex_unlock(&counter->mutex);

    return result;
}

// Set new value
void counter_set(SafeCounter* counter, int new_value) {
    if (!counter) return;

    pthread_mutex_lock(&counter->mutex);
    counter->value = new_value;
    pthread_mutex_unlock(&counter->mutex);
}

// Cleanup
void counter_destroy(SafeCounter* counter) {
    if (!counter) return;

    pthread_mutex_destroy(&counter->mutex);
    free(counter);
}
```

**Key Features:**
- Error checking on all operations
- Consistent locking pattern
- Return values for increment/decrement operations
- Proper cleanup function

---

## 4. Memory Management Focus

### Problem
```c
// "Who should free this memory?"
char* create_message(const char* name) {
    char* msg = malloc(100);
    sprintf(msg, "Hello %s", name);
    return msg;  // Caller must free!
}
```

**Answer**: The **caller** must free the returned pointer since the function allocates memory and transfers ownership.

### Solution 1: Documented Ownership
```c
char* create_message_v1(const char* name) {
    char* msg = malloc(100);
    if (!msg) return NULL;  // Check allocation

    sprintf(msg, "Hello %s", name);
    return msg;  // CALLER OWNS: Must call free() on returned pointer
}
```

### Solution 2: Safer with Bounds Checking
```c
char* create_message_v2(const char* name) {
    if (!name) return NULL;

    size_t name_len = strlen(name);
    size_t total_len = 6 + name_len + 1;  // "Hello " + name + '\0'

    char* msg = malloc(total_len);
    if (!msg) return NULL;

    snprintf(msg, total_len, "Hello %s", name);
    return msg;  // CALLER OWNS: Must call free() on returned pointer
}
```

### Solution 3: Caller-Provided Buffer
```c
int create_message_v3(const char* name, char* buffer, size_t buffer_size) {
    if (!name || !buffer || buffer_size == 0) return -1;

    int result = snprintf(buffer, buffer_size, "Hello %s", name);
    return (result >= 0 && result < buffer_size) ? 0 : -1;
}

// Usage:
char buffer[100];
if (create_message_v3("World", buffer, sizeof(buffer)) == 0) {
    printf("%s\n", buffer);
    // No need to free - using stack buffer
}
```

### Solution 4: Static Buffer (Limited Use)
```c
const char* create_message_v4(const char* name) {
    static char buffer[256];  // WARNING: Not thread-safe!

    if (!name) return NULL;
    snprintf(buffer, sizeof(buffer), "Hello %s", name);
    return buffer;  // CALLER DOES NOT OWN: Do not free!
}
```

**Warning**: This approach is not thread-safe and has limited use cases.

### Solution 5: Handle-Based Cleanup
```c
typedef struct {
    char* message;
    void (*cleanup)(void*);
} MessageHandle;

MessageHandle* create_message_v5(const char* name) {
    MessageHandle* handle = malloc(sizeof(MessageHandle));
    if (!handle) return NULL;

    handle->message = create_message_v2(name);
    if (!handle->message) {
        free(handle);
        return NULL;
    }

    handle->cleanup = (void(*)(void*))free;
    return handle;
}

void message_destroy(MessageHandle* handle) {
    if (!handle) return;

    if (handle->cleanup && handle->message) {
        handle->cleanup(handle->message);
    }
    free(handle);
}

// Usage:
MessageHandle* handle = create_message_v5("World");
if (handle) {
    printf("Message: %s\n", handle->message);
    message_destroy(handle);  // Cleanup handled automatically
}
```

### Trade-offs Summary

| Approach | Pros | Cons |
|----------|------|------|
| Malloc + Return | Simple, flexible | Caller must remember to free |
| Caller Buffer | No malloc, predictable | Requires buffer size management |
| Static Buffer | No malloc, simple | Not thread-safe, limited reuse |
| Handle Pattern | Automatic cleanup | More complex, overhead |

---

## Interview Tips

### 1. Debugging Exercises
- **Identify the shared state** first
- **Explain why** it's a race condition
- **Show multiple solution approaches**
- **Discuss trade-offs** (performance vs simplicity)

### 2. Conceptual Questions
- **Give definitions AND examples**
- **Discuss real-world use cases**
- **Mention performance implications**
- **Show awareness of alternatives**

### 3. Implementations
- **Start simple, add features incrementally**
- **Always check for error conditions**
- **Document ownership and thread safety**
- **Consider edge cases**

### 4. Memory Management
- **Always document who owns what**
- **Provide multiple solution approaches**
- **Consider safety vs performance trade-offs**
- **Think about error handling**

### General Strategy
1. **Ask clarifying questions** about requirements
2. **Start with the simplest correct solution**
3. **Explain your reasoning** as you code
4. **Discuss improvements and alternatives**
5. **Consider error cases and edge conditions**
6. **Be prepared to debug or modify your solution**

### Common Follow-up Questions
- "How would you test this?"
- "What happens under high load?"
- "How would you make this more efficient?"
- "What are the failure modes?"
- "How would you debug race conditions in this code?"

Remember: Interviewers want to see your **thought process** and **problem-solving approach**, not just the final code.