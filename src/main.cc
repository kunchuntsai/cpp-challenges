#include <iostream>

#include "../include/ring_buffer.h"
#include "../include/unit_test.h"

int main() {
    std::cout << "Run main()" << std::endl;

    RingBuffer rb(5);
    rb.push(10.f);
    rb.push(20.f);
    rb.push(30.f);
    rb.push(40.f);
    rb.push(50.f);

    float value;
    value = rb.pop();
    value = rb.pop();
    value = rb.pop();
    return 0;
}