// Challenge 1: Implement a circular buffer
// Implement a circular buffer class that can store a fixed number of elements.
// It should support the following operations:
// - push(element): Add an element to the buffer
// - pop(): Remove and return the oldest element
// - isFull(): Check if the buffer is full
// - isEmpty(): Check if the buffer is empty
#include <iostream>
#include <stdexcept>

class RingBuffer {
private:
    /* buffer size */
    int Size = 0;
    /* index for output data */
    int head = 0;
    /* index for input data */
    int tail = 0;
    /* index for output data */
    bool full = false;
    /* a pointer to hold the memory */
    float* buffer = nullptr;

    /*
    buffer [5] = [0, 0, 0, 0, 0, 0]
    head = 0
    tail = 0
    full = false
    */
public:
    RingBuffer(int size) : Size(size) {
        if (Size <= 0) {
            throw std::runtime_error("Size is invalid");
        } else {
            buffer = new float[Size];
            std::fill(buffer, buffer + Size, 0.0f);
        }
    }

    ~RingBuffer() {
        delete[] buffer;
    }

    void add(float value) {
        buffer[tail] = value;
        tail = (tail + 1) % Size;
        full = (head == tail);

        print();
    }

    float pop() {
        if (isEmpty()) {
            throw std::runtime_error("Buffer is empty");
        }

        float value = buffer[head];
        head = (head + 1) % Size;
        full = false;

        print();
        return value;
    }

    bool isEmpty() const {
        return !full && (head == tail);
    }

    bool isFull() const {
        return full;
    }

    void print() const {
        std::cout << "Buffer: ";
        for (int i = 0; i < Size; i++) {
            std::cout << buffer[i] << ", ";
        }
        std::cout << "(h: " << head << ", t: " << tail << ", f: " << full << std::endl;
    }
};

int main(int argc, char **argv) {
    std::cout << "Run main()" << std::endl;

    RingBuffer rb(5);
    rb.add(10.f);
    rb.add(20.f);
    rb.add(30.f);
    rb.add(40.f);
    rb.add(50.f);

    float value;
    value = rb.pop();
    value = rb.pop();
    value = rb.pop();

    return 0;
}
