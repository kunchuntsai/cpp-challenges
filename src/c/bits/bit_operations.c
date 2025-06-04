#include <stdio.h>
#include <stdint.h>

// Function to print binary representation of a number
void print_binary(uint8_t num) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
    printf("\n");
}

// Function to set a specific bit
uint8_t set_bit(uint8_t num, int pos) {
    return num | (1 << pos);
}

// Function to clear a specific bit
uint8_t clear_bit(uint8_t num, int pos) {
    return num & ~(1 << pos);
}

// Function to toggle a specific bit
uint8_t toggle_bit(uint8_t num, int pos) {
    return num ^ (1 << pos);
}

// Function to check if a bit is set
int is_bit_set(uint8_t num, int pos) {
    return (num >> pos) & 1;
}

// Function to count set bits
int count_set_bits(uint8_t num) {
    int count = 0;
    while (num) {
        count += num & 1;
        num >>= 1;
    }
    return count;
}

int main() {
    printf("Bit Manipulation Examples\n");
    printf("=======================\n\n");

    uint8_t num = 0b10101010;  // 170 in decimal

    printf("1. Basic Bitwise Operations:\n");
    printf("Original number: %d (binary: ", num);
    print_binary(num);

    printf("\n2. Setting/Clearing/Toggling Bits:\n");
    // Set bit 3
    uint8_t set_result = set_bit(num, 3);
    printf("After setting bit 3: %d (binary: ", set_result);
    print_binary(set_result);

    // Clear bit 1
    uint8_t clear_result = clear_bit(num, 1);
    printf("After clearing bit 1: %d (binary: ", clear_result);
    print_binary(clear_result);

    // Toggle bit 5
    uint8_t toggle_result = toggle_bit(num, 5);
    printf("After toggling bit 5: %d (binary: ", toggle_result);
    print_binary(toggle_result);

    printf("\n3. Bit Masking Examples:\n");
    // Extract lower 4 bits
    uint8_t lower_bits = num & 0x0F;
    printf("Lower 4 bits: %d (binary: ", lower_bits);
    print_binary(lower_bits);

    // Extract upper 4 bits
    uint8_t upper_bits = (num >> 4) & 0x0F;
    printf("Upper 4 bits: %d (binary: ", upper_bits);
    print_binary(upper_bits);

    printf("\n4. Bit Counting:\n");
    printf("Number of set bits in %d: %d\n", num, count_set_bits(num));

    printf("\n5. Bit Shifting Examples:\n");
    printf("Left shift by 2: %d (binary: ", num << 2);
    print_binary(num << 2);
    printf("Right shift by 2: %d (binary: ", num >> 2);
    print_binary(num >> 2);

    return 0;
} 