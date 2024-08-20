#include <iostream>

#include "../include/ring_buffer.h"
#include "../include/unit_test.h"

int main() {
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