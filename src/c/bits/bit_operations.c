#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Function to print binary representation
void print_binary(uint32_t num, int bits) {
    for (int i = bits - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
        if (i % 4 == 0 && i > 0) printf(" "); // Space every 4 bits for readability
    }
    printf("\n");
}

/*
================================================================================
INTERVIEW SECTION 1: "SET/CLEAR/TOGGLE BITS"
Core hardware register operations
================================================================================
*/

// Set a specific bit (turn it ON)
uint32_t set_bit(uint32_t num, int pos) {
    return num | (1U << pos);
}

// Clear a specific bit (turn it OFF)
uint32_t clear_bit(uint32_t num, int pos) {
    return num & ~(1U << pos);
}

// Toggle a specific bit (flip it)
uint32_t toggle_bit(uint32_t num, int pos) {
    return num ^ (1U << pos);
}

// Check if a bit is set
int is_bit_set(uint32_t num, int pos) {
    return (num >> pos) & 1;
}

void demonstrate_bit_operations() {
    printf("=== BIT SET/CLEAR/TOGGLE OPERATIONS ===\n");
    
    uint8_t control_reg = 0b00001010;  // Simulating a hardware control register
    printf("Initial control register: 0x%02X (", control_reg);
    print_binary(control_reg, 8);
    
    // Set bit 0 (enable flag)
    control_reg = set_bit(control_reg, 0);
    printf("After setting bit 0:     0x%02X (", control_reg);
    print_binary(control_reg, 8);
    
    // Clear bit 3 (disable interrupt)
    control_reg = clear_bit(control_reg, 3);
    printf("After clearing bit 3:    0x%02X (", control_reg);
    print_binary(control_reg, 8);
    
    // Toggle bit 2 (flip mode)
    control_reg = toggle_bit(control_reg, 2);
    printf("After toggling bit 2:    0x%02X (", control_reg);
    print_binary(control_reg, 8);
    
    printf("\n");
}

/*
================================================================================
INTERVIEW SECTION 2: "BIT MASKING"
Essential for data extraction and hardware register manipulation
================================================================================
*/

// Extract specific bits using mask
uint32_t extract_bits(uint32_t num, int start, int length) {
    uint32_t mask = (1U << length) - 1;  // Create mask with 'length' ones
    return (num >> start) & mask;
}

// Pack multiple values into a single integer
uint32_t pack_data(uint8_t a, uint8_t b, uint8_t c, uint8_t d) {
    return ((uint32_t)a << 24) | ((uint32_t)b << 16) | ((uint32_t)c << 8) | d;
}

// Unpack data from packed integer
void unpack_data(uint32_t packed, uint8_t *a, uint8_t *b, uint8_t *c, uint8_t *d) {
    *a = (packed >> 24) & 0xFF;
    *b = (packed >> 16) & 0xFF;
    *c = (packed >> 8) & 0xFF;
    *d = packed & 0xFF;
}

void demonstrate_bit_masking() {
    printf("=== BIT MASKING OPERATIONS ===\n");
    
    // Example 1: Status register with multiple fields
    uint16_t status_reg = 0b1101001011010110;
    printf("Status register: 0x%04X (", status_reg);
    print_binary(status_reg, 16);
    
    // Extract different fields using masks
    uint8_t error_code = extract_bits(status_reg, 0, 4);    // Bits 0-3
    uint8_t device_id = extract_bits(status_reg, 4, 3);     // Bits 4-6
    uint8_t flags = extract_bits(status_reg, 8, 4);         // Bits 8-11
    
    printf("Error code (bits 0-3): %d\n", error_code);
    printf("Device ID (bits 4-6):  %d\n", device_id);
    printf("Flags (bits 8-11):     %d\n", flags);
    
    // Example 2: Data packing/unpacking
    printf("\nData Packing Example:\n");
    uint8_t r = 255, g = 128, b = 64, a = 32;
    uint32_t packed_color = pack_data(r, g, b, a);
    printf("Packed RGBA: 0x%08X\n", packed_color);
    
    uint8_t ur, ug, ub, ua;
    unpack_data(packed_color, &ur, &ug, &ub, &ua);
    printf("Unpacked: R=%d, G=%d, B=%d, A=%d\n\n", ur, ug, ub, ua);
}

/*
================================================================================
INTERVIEW SECTION 3: "REGISTER MANIPULATION"
Direct hardware programming patterns
================================================================================
*/

// Simulate hardware register operations
typedef struct {
    volatile uint32_t control;
    volatile uint32_t status;
    volatile uint32_t data;
    volatile uint32_t interrupt;
} hardware_registers_t;

// Set multiple bits atomically (important for hardware)
void set_register_bits(volatile uint32_t *reg, uint32_t mask) {
    *reg |= mask;
}

// Clear multiple bits atomically
void clear_register_bits(volatile uint32_t *reg, uint32_t mask) {
    *reg &= ~mask;
}

// Modify specific field in register
void modify_register_field(volatile uint32_t *reg, uint32_t field_mask, 
                          uint32_t field_value, int field_shift) {
    *reg = (*reg & ~field_mask) | ((field_value << field_shift) & field_mask);
}

void demonstrate_register_manipulation() {
    printf("=== HARDWARE REGISTER MANIPULATION ===\n");
    
    // Simulate hardware registers
    hardware_registers_t hw = {0};
    
    printf("Initial registers:\n");
    printf("Control: 0x%08X, Status: 0x%08X\n\n", hw.control, hw.status);
    
    // Set multiple control bits
    #define ENABLE_BIT     (1U << 0)
    #define START_BIT      (1U << 1)
    #define INT_ENABLE_BIT (1U << 8)
    
    set_register_bits(&hw.control, ENABLE_BIT | START_BIT | INT_ENABLE_BIT);
    printf("After setting control bits: 0x%08X (", hw.control);
    print_binary(hw.control, 16);
    
    // Modify a specific field (e.g., 4-bit clock divider at bits 4-7)
    #define CLOCK_DIV_MASK  (0xF << 4)
    uint32_t new_divider = 5;  // Set divider to 5
    modify_register_field(&hw.control, CLOCK_DIV_MASK, new_divider, 4);
    
    printf("After setting clock divider to %d: 0x%08X (", new_divider, hw.control);
    print_binary(hw.control, 16);
    
    printf("\n");
}

/*
================================================================================
INTERVIEW SECTION 4: "COMMON BIT MANIPULATION INTERVIEW QUESTIONS"
================================================================================
*/

// Count number of set bits (Population count)
int count_set_bits(uint32_t n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

// Brian Kernighan's algorithm - more efficient
int count_set_bits_efficient(uint32_t n) {
    int count = 0;
    while (n) {
        n = n & (n - 1);  // Clears the lowest set bit
        count++;
    }
    return count;
}

// Check if number is power of 2
int is_power_of_2(uint32_t n) {
    return n > 0 && (n & (n - 1)) == 0;
}

// Find the only non-duplicate number (XOR property)
int find_single_number(int arr[], int size) {
    int result = 0;
    for (int i = 0; i < size; i++) {
        result ^= arr[i];
    }
    return result;
}

// Reverse bits in a 32-bit integer
uint32_t reverse_bits(uint32_t n) {
    uint32_t result = 0;
    for (int i = 0; i < 32; i++) {
        result = (result << 1) | (n & 1);
        n >>= 1;
    }
    return result;
}

void demonstrate_interview_questions() {
    printf("=== COMMON INTERVIEW QUESTIONS ===\n");
    
    // Question 1: Count set bits
    uint32_t num = 0b11010110;
    printf("Number: %d (", num);
    print_binary(num, 8);
    printf("Set bits (method 1): %d\n", count_set_bits(num));
    printf("Set bits (efficient): %d\n", count_set_bits_efficient(num));
    
    // Question 2: Power of 2 check
    int test_nums[] = {16, 17, 32, 33, 64};
    printf("\nPower of 2 checks:\n");
    for (int i = 0; i < 5; i++) {
        printf("%d is %spower of 2\n", test_nums[i], 
               is_power_of_2(test_nums[i]) ? "" : "NOT ");
    }
    
    // Question 3: Find single number
    int arr[] = {2, 3, 5, 4, 5, 3, 4};  // 2 appears once, others twice
    int single = find_single_number(arr, 7);
    printf("\nSingle number in array: %d\n", single);
    
    // Question 4: Bit reversal
    uint8_t original = 0b11010010;
    uint32_t reversed = reverse_bits(original);
    printf("\nOriginal:  ");
    print_binary(original, 8);
    printf("Reversed:  ");
    print_binary(reversed >> 24, 8);  // Show only relevant 8 bits
    
    printf("\n");
}

/*
================================================================================
INTERVIEW SECTION 5: "EMBEDDED SYSTEMS BIT OPERATIONS"
Real-world hardware control scenarios
================================================================================
*/

void demonstrate_embedded_scenarios() {
    printf("=== EMBEDDED SYSTEMS SCENARIOS ===\n");
    
    // Scenario 1: GPIO Port Control
    printf("1. GPIO Port Control:\n");
    uint8_t gpio_port = 0x00;
    
    // Set pins 0, 2, 4 as outputs (1 = output, 0 = input)
    uint8_t output_mask = (1 << 0) | (1 << 2) | (1 << 4);
    gpio_port |= output_mask;
    printf("GPIO direction register: 0x%02X (", gpio_port);
    print_binary(gpio_port, 8);
    
    // Scenario 2: ADC Configuration
    printf("\n2. ADC Configuration Register:\n");
    uint16_t adc_config = 0x0000;
    
    // Set resolution (bits 8-9): 00=8bit, 01=10bit, 10=12bit, 11=16bit
    adc_config = (adc_config & ~(0x3 << 8)) | (0x2 << 8);  // 12-bit
    
    // Set reference voltage (bits 6-7): 00=VDD, 01=internal, 10=external
    adc_config = (adc_config & ~(0x3 << 6)) | (0x1 << 6);  // Internal
    
    // Enable ADC (bit 0)
    adc_config |= (1 << 0);
    
    printf("ADC config: 0x%04X (", adc_config);
    print_binary(adc_config, 16);
    
    // Scenario 3: Interrupt Flag Clearing
    printf("\n3. Interrupt Flag Management:\n");
    uint8_t interrupt_flags = 0b11010101;  // Multiple interrupts pending
    printf("Interrupt flags: 0x%02X (", interrupt_flags);
    print_binary(interrupt_flags, 8);
    
    // Clear specific interrupt (bit 2) by writing 1 to it
    interrupt_flags &= ~(1 << 2);
    printf("After clearing bit 2: 0x%02X (", interrupt_flags);
    print_binary(interrupt_flags, 8);
    
    printf("\n");
}

int main() {
    printf("COMPREHENSIVE BIT MANIPULATION FOR C INTERVIEWS\n");
    printf("===============================================\n\n");
    
    demonstrate_bit_operations();
    demonstrate_bit_masking();
    demonstrate_register_manipulation();
    demonstrate_interview_questions();
    demonstrate_embedded_scenarios();
    
    printf("=== KEY TAKEAWAYS ===\n");
    printf("• Master set/clear/toggle: Essential for hardware control\n");
    printf("• Understand masking: Critical for data extraction\n");
    printf("• Practice register ops: Direct embedded systems mapping\n");
    printf("• Know efficient algorithms: Shows advanced understanding\n");
    printf("• Think hardware-first: C is about direct hardware control\n");
    
    return 0;
}