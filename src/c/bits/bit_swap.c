#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Function prototype
void print_binary(int n, int bits);

/*
================================================================================
INTERVIEW QUESTION 1: "Implement swap without temporary variable"
================================================================================
*/

// Method 1: XOR Swap (most common answer)
void swap_without_temp_xor(int *a, int *b) {
    printf("XOR Swap Implementation:\n");
    printf("Before: a=%d, b=%d\n", *a, *b);
    
    if (a != b) {  // Critical safety check!
        *a = *a ^ *b;  // a now holds a⊕b
        printf("Step 1: a = a^b = %d\n", *a);
        
        *b = *a ^ *b;  // b = (a⊕b)⊕b = a
        printf("Step 2: b = a^b = %d (now b has original a)\n", *b);
        
        *a = *a ^ *b;  // a = (a⊕b)⊕a = b
        printf("Step 3: a = a^b = %d (now a has original b)\n", *a);
    }
    printf("After: a=%d, b=%d\n\n", *a, *b);
}

// Method 2: Arithmetic Swap (alternative answer)
void swap_without_temp_arithmetic(int *a, int *b) {
    printf("Arithmetic Swap Implementation:\n");
    printf("Before: a=%d, b=%d\n", *a, *b);
    
    if (a != b && *a != 0 && *b != 0) {  // Avoid overflow issues
        *a = *a + *b;  // a = A + B
        printf("Step 1: a = a+b = %d\n", *a);
        
        *b = *a - *b;  // b = (A+B) - B = A
        printf("Step 2: b = a-b = %d\n", *b);
        
        *a = *a - *b;  // a = (A+B) - A = B
        printf("Step 3: a = a-b = %d\n", *a);
    }
    printf("After: a=%d, b=%d\n\n", *a, *b);
}

// Helper function to print binary representation
void print_binary(int n, int bits) {
    for (int i = bits - 1; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
    }
}

/*
================================================================================
INTERVIEW QUESTION 3: "When would you use XOR swap in production code?"
================================================================================
*/

// Example of good production use case
void embedded_sensor_example() {
    printf("=== PRODUCTION EXAMPLE: Embedded Sensor Data ===\n");
    
    // Simulating a memory-constrained microcontroller scenario
    uint16_t sensor_readings[4] = {1023, 512, 256, 128};
    
    printf("Sensor readings before sorting: ");
    for (int i = 0; i < 4; i++) {
        printf("%d ", sensor_readings[i]);
    }
    printf("\n");
    
    // Simple bubble sort using XOR swap (in embedded system with no extra RAM)
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3 - i; j++) {
            if (sensor_readings[j] > sensor_readings[j + 1]) {
                // XOR swap - no temporary variable needed
                sensor_readings[j] ^= sensor_readings[j + 1];
                sensor_readings[j + 1] ^= sensor_readings[j];
                sensor_readings[j] ^= sensor_readings[j + 1];
            }
        }
    }
    
    printf("Sensor readings after sorting:  ");
    for (int i = 0; i < 4; i++) {
        printf("%d ", sensor_readings[i]);
    }
    printf("\n\n");
}

/*
================================================================================
INTERVIEW QUESTION 4: "What are the limitations of XOR swap?"
================================================================================
*/

// Demonstrate the float limitation
void demonstrate_float_limitation() {
    printf("=== FLOAT LIMITATION DEMO ===\n");
    
    float a = 3.14f, b = 2.71f;
    printf("Original floats: a=%.2f, b=%.2f\n", a, b);
    
    // This is WRONG - don't do this!
    // We'll show what happens when you try to XOR the bit patterns
    int *int_a = (int*)&a;
    int *int_b = (int*)&b;
    
    printf("Float bit patterns:\n");
    printf("a as int: %d (0x%08X)\n", *int_a, *int_a);
    printf("b as int: %d (0x%08X)\n", *int_b, *int_b);
    
    // Don't actually do the XOR swap on floats - it will give garbage!
    printf("❌ XOR swapping these bit patterns would give meaningless results!\n");
    printf("✅ Use regular swap for floats: temp=a; a=b; b=temp;\n\n");
}

int main() {
    printf("XOR SWAP INTERVIEW QUESTIONS & ANSWERS\n");
    printf("=====================================\n\n");
    
    // Question 1: Implementation
    printf("QUESTION 1: Implement swap without temporary variable\n");
    printf("---------------------------------------------------\n");
    int a = 15, b = 25;
    swap_without_temp_xor(&a, &b);
    
    int c = 100, d = 200;
    swap_without_temp_arithmetic(&c, &d);
    
    // Question 1: Implementation
    printf("QUESTION 3: When would you use XOR swap in production code\n");
    printf("---------------------------------------------------\n");
    embedded_sensor_example();
    
    // Question 4: Limitations
    printf("QUESTION 4: What are the limitations of XOR swap?\n");
    printf("---------------------------------------------------\n");
    demonstrate_float_limitation();
    
    return 0;
}