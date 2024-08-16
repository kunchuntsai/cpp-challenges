// Challenge 4: Implement a Thread Pool
// Implement a thread pool that can manage a fixed number of worker threads.
// It should support the following operations:
// - Constructor that creates a specified number of worker threads
// - enqueue(task): Add a task to the pool's queue
// - shutdown(): Stop all threads and clean up resources
// The thread pool should be able to handle any type of task (use templates or std::function)

class ThreadPool {
public:
    ThreadPool(size_t numThreads) {
        // TODO: Initialize the thread pool with numThreads worker threads
    }

    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args) 
        -> std::future<typename std::result_of<F(Args...)>::type> {
        // TODO: Implement task enqueueing
    }

    ~ThreadPool() {
        // TODO: Implement proper shutdown
    }

private:
    // TODO: Add necessary member variables and helper functions
};
