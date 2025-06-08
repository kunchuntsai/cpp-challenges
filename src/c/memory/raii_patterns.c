// ========================================
// MULTI-FUNCTION & MULTI-THREADING MEMORY MANAGEMENT
// ========================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>

// ========================================
// PATTERN 1: CLEAR OWNERSHIP TRANSFER
// ========================================

typedef struct {
    char* data;
    size_t size;
    int owner_id;  // For debugging ownership
} DataBuffer;

// Creator owns the buffer
DataBuffer* create_buffer(const char* initial_data, int owner_id) {
    DataBuffer* buf = malloc(sizeof(DataBuffer));
    if (!buf) return NULL;
    
    buf->size = strlen(initial_data) + 1;
    buf->data = malloc(buf->size);
    if (!buf->data) {
        free(buf);
        return NULL;
    }
    
    strcpy(buf->data, initial_data);
    buf->owner_id = owner_id;
    printf("Buffer created by owner %d\n", owner_id);
    return buf;
}

// Function that borrows data (doesn't own it)
int process_data_borrow(const DataBuffer* buf) {
    if (!buf || !buf->data) return -1;
    
    printf("Processing data (borrowed): %s\n", buf->data);
    // Can read, but shouldn't modify or free
    return 0;
}

// Function that takes ownership (caller gives up ownership)
int process_data_take_ownership(DataBuffer* buf) {
    if (!buf) return -1;
    
    printf("Processing data (owned): %s\n", buf->data);
    
    // Modify the data
    strcat(buf->data, " [processed]");
    
    // Owner is responsible for cleanup
    free(buf->data);
    free(buf);
    return 0;
}

// Function that returns ownership to caller
DataBuffer* process_data_return_ownership(DataBuffer* buf, int new_owner_id) {
    if (!buf) return NULL;
    
    // Process the data
    printf("Processing and returning data\n");
    
    // Create new buffer with processed data
    size_t new_size = buf->size + 20;
    char* new_data = malloc(new_size);
    if (!new_data) {
        // Cleanup original on failure
        free(buf->data);
        free(buf);
        return NULL;
    }
    
    snprintf(new_data, new_size, "%s [processed by %d]", buf->data, new_owner_id);
    printf("Processed data: %s\n", new_data);
    
    // Cleanup old buffer
    free(buf->data);
    free(buf);
    
    // Create new buffer
    DataBuffer* new_buf = malloc(sizeof(DataBuffer));
    if (!new_buf) {
        free(new_data);
        return NULL;
    }
    
    new_buf->data = new_data;
    new_buf->size = new_size;
    new_buf->owner_id = new_owner_id;
    
    return new_buf;
}

void ownership_example() {
    printf("\n=== OWNERSHIP TRANSFER EXAMPLE ===\n");
    printf("Demonstrating clear ownership transfer between functions:\n");
    printf("--------------------------------------------------------\n");
    
    // Create buffer (caller owns)
    DataBuffer* buf = create_buffer("Hello World", 1);
    if (!buf) return;
    
    // Borrow data (ownership stays with caller)
    process_data_borrow(buf);
    
    // Transfer ownership (buf becomes invalid after this call)
    buf = process_data_return_ownership(buf, 2);
    
    // Final cleanup (current owner)
    if (buf) {
        printf("--------------------------------------------------------\n");
        printf("Final cleanup by owner %d\n", buf->owner_id);
        free(buf->data);
        free(buf);
    }
}

// ========================================
// PATTERN 2: REFERENCE COUNTING
// ========================================

typedef struct {
    char* data;
    size_t size;
    int ref_count;
    pthread_mutex_t mutex;
} RefCountedBuffer;

RefCountedBuffer* refbuf_create(const char* data) {
    RefCountedBuffer* buf = malloc(sizeof(RefCountedBuffer));
    if (!buf) return NULL;
    
    buf->size = strlen(data) + 1;
    buf->data = malloc(buf->size);
    if (!buf->data) {
        free(buf);
        return NULL;
    }
    
    strcpy(buf->data, data);
    buf->ref_count = 1;  // Creator gets first reference
    
    if (pthread_mutex_init(&buf->mutex, NULL) != 0) {
        free(buf->data);
        free(buf);
        return NULL;
    }
    
    printf("RefBuffer created,  ref_count=1\n");
    return buf;
}

// Increment reference count (thread-safe)
RefCountedBuffer* refbuf_retain(RefCountedBuffer* buf) {
    if (!buf) return NULL;
    
    pthread_mutex_lock(&buf->mutex);
    buf->ref_count++;
    printf("RefBuffer + +, ref_count=%d\n", buf->ref_count);
    pthread_mutex_unlock(&buf->mutex);
    
    return buf;
}

// Decrement reference count, free if reaches 0 (thread-safe)
void refbuf_release(RefCountedBuffer* buf) {
    if (!buf) return;
    
    pthread_mutex_lock(&buf->mutex);
    buf->ref_count--;
    int should_free = (buf->ref_count == 0);
    printf("RefBuffer - -, ref_count=%d\n", buf->ref_count);
    pthread_mutex_unlock(&buf->mutex);
    
    if (should_free) {
        printf("RefBuffer destroyed\n");
        pthread_mutex_destroy(&buf->mutex);
        free(buf->data);
        free(buf);
    }
}

// Function that uses reference counting
void process_with_refcount(RefCountedBuffer* buf) {
    // Retain reference while using
    RefCountedBuffer* local_ref = refbuf_retain(buf);
    
    printf("Processing: %s\n", local_ref->data);
    
    // Simulate work
    usleep(100000);  // 100ms
    
    // Release when done
    refbuf_release(local_ref);
}

void* ref_counting_thread(void* arg) {
    RefCountedBuffer* buf = (RefCountedBuffer*)arg;
    
    for (int i = 0; i < 3; i++) {
        process_with_refcount(buf);
        usleep(50000);
    }
    
    return NULL;
}

void ref_counting_example() {
    printf("\n=== REFERENCE COUNTING EXAMPLE ===\n");
    printf("Demonstrating shared ownership with reference counting:\n");
    printf("--------------------------------------------------------\n");
    
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
    
    printf("--------------------------------------------------------\n");
    // Release original reference
    refbuf_release(buf);
}

// ========================================
// PATTERN 3: THREAD-SAFE QUEUE WITH OWNERSHIP
// ========================================

typedef struct QueueNode {
    void* data;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* head;
    QueueNode* tail;
    pthread_mutex_t mutex;
    pthread_cond_t not_empty;
    int shutdown;
} ThreadSafeQueue;

ThreadSafeQueue* queue_create() {
    ThreadSafeQueue* q = malloc(sizeof(ThreadSafeQueue));
    if (!q) return NULL;
    
    q->head = q->tail = NULL;
    q->shutdown = 0;
    
    if (pthread_mutex_init(&q->mutex, NULL) != 0) {
        free(q);
        return NULL;
    }
    
    if (pthread_cond_init(&q->not_empty, NULL) != 0) {
        pthread_mutex_destroy(&q->mutex);
        free(q);
        return NULL;
    }
    
    return q;
}

// Producer: Transfer ownership to queue
int queue_push(ThreadSafeQueue* q, void* data) {
    if (!q) return -1;
    
    QueueNode* node = malloc(sizeof(QueueNode));
    if (!node) return -1;
    
    node->data = data;
    node->next = NULL;
    
    pthread_mutex_lock(&q->mutex);
    
    if (q->shutdown) {
        pthread_mutex_unlock(&q->mutex);
        free(node);
        return -1;
    }
    
    if (q->tail) {
        q->tail->next = node;
    } else {
        q->head = node;
    }
    q->tail = node;
    
    pthread_cond_signal(&q->not_empty);
    pthread_mutex_unlock(&q->mutex);
    
    return 0;
}

// Consumer: Receive ownership from queue
void* queue_pop(ThreadSafeQueue* q) {
    if (!q) return NULL;
    
    pthread_mutex_lock(&q->mutex);
    
    while (!q->head && !q->shutdown) {
        pthread_cond_wait(&q->not_empty, &q->mutex);
    }
    
    if (q->shutdown && !q->head) {
        pthread_mutex_unlock(&q->mutex);
        return NULL;
    }
    
    QueueNode* node = q->head;
    void* data = node->data;
    
    q->head = node->next;
    if (!q->head) {
        q->tail = NULL;
    }
    
    pthread_mutex_unlock(&q->mutex);
    
    free(node);
    return data;  // Ownership transferred to caller
}

void queue_shutdown(ThreadSafeQueue* q) {
    if (!q) return;
    
    pthread_mutex_lock(&q->mutex);
    q->shutdown = 1;
    pthread_cond_broadcast(&q->not_empty);
    pthread_mutex_unlock(&q->mutex);
}

void queue_destroy(ThreadSafeQueue* q) {
    if (!q) return;
    
    // Cleanup remaining items
    void* item;
    while ((item = queue_pop(q)) != NULL) {
        free(item);  // Assumes items are malloc'd
    }
    
    pthread_mutex_destroy(&q->mutex);
    pthread_cond_destroy(&q->not_empty);
    free(q);
}

// Producer thread function
void* producer_thread(void* arg) {
    ThreadSafeQueue* q = (ThreadSafeQueue*)arg;
    for (int i = 0; i < 5; i++) {
        // Create data for the queue
        char* data = malloc(50);
        snprintf(data, 50, "Message %d from producer", i);
        
        printf("Producer: Pushing %s\n", data);
        if (queue_push(q, data) != 0) {
            printf("Producer: Failed to push data\n");
            free(data);
        }
        
        usleep(100000);  // 100ms delay
    }
    return NULL;
}

// Consumer thread function
void* consumer_thread(void* arg) {
    ThreadSafeQueue* q = (ThreadSafeQueue*)arg;
    while (1) {
        char* data = (char*)queue_pop(q);
        if (!data) {
            printf("Consumer: Queue shutdown\n");
            break;
        }
        
        printf("Consumer: Received %s\n", data);
        free(data);  // Consumer owns the data and must free it
        usleep(150000);  // 150ms delay
    }
    return NULL;
}

void thread_safe_queue_example() {
    printf("\n=== THREAD-SAFE QUEUE EXAMPLE ===\n");
    printf("Demonstrating producer-consumer pattern with ownership transfer:\n");
    printf("--------------------------------------------------------\n");
    
    // Create the queue
    ThreadSafeQueue* queue = queue_create();
    if (!queue) {
        printf("Failed to create queue\n");
        return;
    }
    
    // Create producer and consumer threads
    pthread_t producer, consumer;
    pthread_create(&producer, NULL, producer_thread, queue);
    pthread_create(&consumer, NULL, consumer_thread, queue);
    
    // Wait for producer to finish
    pthread_join(producer, NULL);
    
    // Shutdown queue and wait for consumer
    queue_shutdown(queue);
    pthread_join(consumer, NULL);
    
    // Cleanup
    queue_destroy(queue);
    printf("--------------------------------------------------------\n");
}

// ========================================
// PATTERN 4: THREAD POOL WITH DATA PROCESSING
// ========================================

typedef struct {
    void* data;
    void (*process_func)(void*);
    void (*cleanup_func)(void*);
} WorkItem;

typedef struct {
    ThreadSafeQueue* work_queue;
    pthread_t* threads;
    int num_threads;
    int running;
} ThreadPool;

void* worker_thread(void* arg) {
    ThreadPool* pool = (ThreadPool*)arg;
    
    while (pool->running) {
        WorkItem* item = (WorkItem*)queue_pop(pool->work_queue);
        
        if (!item) break;  // Queue shutdown
        
        // Process the work item
        if (item->process_func) {
            item->process_func(item->data);
        }
        
        // Cleanup the data
        if (item->cleanup_func) {
            item->cleanup_func(item->data);
        }
        
        // Cleanup the work item itself
        free(item);
    }
    
    return NULL;
}

ThreadPool* threadpool_create(int num_threads) {
    ThreadPool* pool = malloc(sizeof(ThreadPool));
    if (!pool) return NULL;
    
    pool->work_queue = queue_create();
    if (!pool->work_queue) {
        free(pool);
        return NULL;
    }
    
    pool->threads = malloc(num_threads * sizeof(pthread_t));
    if (!pool->threads) {
        queue_destroy(pool->work_queue);
        free(pool);
        return NULL;
    }
    
    pool->num_threads = num_threads;
    pool->running = 1;
    
    // Start worker threads
    for (int i = 0; i < num_threads; i++) {
        if (pthread_create(&pool->threads[i], NULL, worker_thread, pool) != 0) {
            // Cleanup on failure
            pool->running = 0;
            queue_shutdown(pool->work_queue);
            for (int j = 0; j < i; j++) {
                pthread_join(pool->threads[j], NULL);
            }
            free(pool->threads);
            queue_destroy(pool->work_queue);
            free(pool);
            return NULL;
        }
    }
    
    return pool;
}

// Submit work to thread pool (transfers ownership of data)
int threadpool_submit(ThreadPool* pool, void* data, 
                     void (*process_func)(void*),
                     void (*cleanup_func)(void*)) {
    if (!pool || !pool->running) return -1;
    
    WorkItem* item = malloc(sizeof(WorkItem));
    if (!item) return -1;
    
    item->data = data;
    item->process_func = process_func;
    item->cleanup_func = cleanup_func;
    
    if (queue_push(pool->work_queue, item) != 0) {
        free(item);
        return -1;
    }
    
    return 0;
}

void threadpool_destroy(ThreadPool* pool) {
    if (!pool) return;
    
    // Signal shutdown
    pool->running = 0;
    queue_shutdown(pool->work_queue);
    
    // Wait for all threads to finish
    for (int i = 0; i < pool->num_threads; i++) {
        pthread_join(pool->threads[i], NULL);
    }
    
    // Cleanup
    free(pool->threads);
    queue_destroy(pool->work_queue);
    free(pool);
}

// Example work functions
void process_string_data(void* data) {
    char* str = (char*)data;
    printf("Thread %lu processing: %s\n", (unsigned long)pthread_self(), str);
    usleep(100000);  // Simulate work
}

void cleanup_string_data(void* data) {
    free(data);
}

void threadpool_example() {
    printf("\n=== THREAD POOL EXAMPLE ===\n");
    printf("Demonstrating work distribution across thread pool:\n");
    printf("--------------------------------------------------------\n");
    
    ThreadPool* pool = threadpool_create(2);
    if (!pool) return;
    
    // Submit work items
    for (int i = 0; i < 5; i++) {
        char* data = malloc(50);
        snprintf(data, 50, "Work item %d", i);
        
        threadpool_submit(pool, data, process_string_data, cleanup_string_data);
    }
    
    // Let work complete
    sleep(1);
    
    printf("--------------------------------------------------------\n");
    threadpool_destroy(pool);
}

// ========================================
// PATTERN 5: SHARED MEMORY WITH COPY SEMANTICS
// ========================================

typedef struct {
    char* data;
    size_t size;
    pthread_rwlock_t rwlock;
} SharedBuffer;

SharedBuffer* shared_buffer_create(const char* initial_data) {
    SharedBuffer* buf = malloc(sizeof(SharedBuffer));
    if (!buf) return NULL;
    
    buf->size = strlen(initial_data) + 1;
    buf->data = malloc(buf->size);
    if (!buf->data) {
        free(buf);
        return NULL;
    }
    
    strcpy(buf->data, initial_data);
    
    if (pthread_rwlock_init(&buf->rwlock, NULL) != 0) {
        free(buf->data);
        free(buf);
        return NULL;
    }
    
    return buf;
}

// Read data (returns copy - caller owns it)
char* shared_buffer_read_copy(SharedBuffer* buf) {
    if (!buf) return NULL;
    
    pthread_rwlock_rdlock(&buf->rwlock);
    
    char* copy = malloc(buf->size);
    if (copy) {
        strcpy(copy, buf->data);
    }
    
    pthread_rwlock_unlock(&buf->rwlock);
    
    return copy;  // Caller owns this copy
}

// Write data (takes copy of input)
int shared_buffer_write(SharedBuffer* buf, const char* new_data) {
    if (!buf || !new_data) return -1;
    
    size_t new_size = strlen(new_data) + 1;
    char* new_buffer = malloc(new_size);
    if (!new_buffer) return -1;
    
    strcpy(new_buffer, new_data);
    
    pthread_rwlock_wrlock(&buf->rwlock);
    
    free(buf->data);
    buf->data = new_buffer;
    buf->size = new_size;
    
    pthread_rwlock_unlock(&buf->rwlock);
    
    return 0;
}

void shared_buffer_destroy(SharedBuffer* buf) {
    if (!buf) return;
    
    pthread_rwlock_destroy(&buf->rwlock);
    free(buf->data);
    free(buf);
}

void shared_memory_example() {
    printf("\n=== SHARED MEMORY EXAMPLE ===\n");
    printf("Demonstrating thread-safe shared memory access:\n");
    printf("--------------------------------------------------------\n");
    
    SharedBuffer* shared = shared_buffer_create("Initial data");
    if (!shared) return;
    
    // Read copies in multiple threads would go here
    char* copy1 = shared_buffer_read_copy(shared);
    if (copy1) {
        printf("Read copy: %s\n", copy1);
        free(copy1);  // Caller owns the copy
    }
    
    // Write new data
    shared_buffer_write(shared, "Updated data");
    
    char* copy2 = shared_buffer_read_copy(shared);
    if (copy2) {
        printf("Read copy after update: %s\n", copy2);
        free(copy2);
    }
    
    printf("--------------------------------------------------------\n");
    shared_buffer_destroy(shared);
}

// ========================================
// MAIN DEMONSTRATION
// ========================================

int main() {
    printf("\n=== MULTI-FUNCTION & MULTI-THREADING PATTERNS ===\n");
    printf("Demonstrating various memory management patterns in C:\n");
    printf("==================================================\n");
    
    ownership_example();
    ref_counting_example();
    thread_safe_queue_example();
    threadpool_example();
    shared_memory_example();
    
    printf("\nAll examples completed successfully!\n");
    return 0;
}

/*
KEY PATTERNS FOR REAL-WORLD SCENARIOS:

1. **CLEAR OWNERSHIP RULES**
   - Document who owns what
   - Use naming conventions (borrow_, take_, return_)
   - Transfer ownership explicitly

2. **REFERENCE COUNTING**
   - Multiple threads can safely share data
   - Automatic cleanup when last reference is released
   - Thread-safe increment/decrement

3. **PRODUCER-CONSUMER QUEUES**
   - Clear ownership transfer points
   - Thread-safe operations
   - Proper cleanup on shutdown

4. **THREAD POOLS**
   - Work items carry their own cleanup functions
   - Each thread processes and cleans up independently
   - Pool manages thread lifecycle

5. **COPY SEMANTICS**
   - Each thread gets its own copy
   - No shared mutable state
   - Simple but memory-intensive

6. **SYNCHRONIZATION PATTERNS**
   - Mutexes for exclusive access
   - Read-write locks for shared reading
   - Condition variables for signaling

INTERVIEW INSIGHTS:
- Demonstrate understanding of thread safety
- Show awareness of ownership transfer
- Explain trade-offs between patterns
- Discuss memory vs. performance considerations
*/ 