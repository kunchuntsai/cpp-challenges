# Bit Manipulation in C

This document covers fundamental bit manipulation concepts and techniques in C programming, with a focus on embedded systems and interview preparation.

## Key Concepts

### 1. Bitwise Operators

- `&` (AND): Sets a bit to 1 only if both bits are 1
- `|` (OR): Sets a bit to 1 if either bit is 1
- `^` (XOR): Sets a bit to 1 if exactly one bit is 1
- `~` (NOT): Inverts all bits
- `<<` (Left Shift): Shifts bits left by specified amount
- `>>` (Right Shift): Shifts bits right by specified amount

### 2. Core Bit Operations

#### Setting a Bit
```c
uint32_t set_bit(uint32_t num, int pos) {
    return num | (1U << pos);
}
```

#### Clearing a Bit
```c
uint32_t clear_bit(uint32_t num, int pos) {
    return num & ~(1U << pos);
}
```

#### Toggling a Bit
```c
uint32_t toggle_bit(uint32_t num, int pos) {
    return num ^ (1U << pos);
}
```

#### Checking a Bit
```c
int is_bit_set(uint32_t num, int pos) {
    return (num >> pos) & 1;
}
```

### 3. Bit Masking Techniques

#### Extracting Bits
```c
uint32_t extract_bits(uint32_t num, int start, int length) {
    uint32_t mask = (1U << length) - 1;
    return (num >> start) & mask;
}
```

#### Data Packing/Unpacking
```c
// Pack multiple values into a single integer
uint32_t pack_data(uint8_t a, uint8_t b, uint8_t c, uint8_t d) {
    return ((uint32_t)a << 24) | ((uint32_t)b << 16) |
           ((uint32_t)c << 8) | d;
}

// Unpack data from packed integer
void unpack_data(uint32_t packed, uint8_t *a, uint8_t *b,
                uint8_t *c, uint8_t *d) {
    *a = (packed >> 24) & 0xFF;
    *b = (packed >> 16) & 0xFF;
    *c = (packed >> 8) & 0xFF;
    *d = packed & 0xFF;
}
```

### 4. Hardware Register Operations

#### Register Structure
```c
typedef struct {
    volatile uint32_t control;
    volatile uint32_t status;
    volatile uint32_t data;
    volatile uint32_t interrupt;
} hardware_registers_t;
```

#### Atomic Register Operations
```c
void set_register_bits(volatile uint32_t *reg, uint32_t mask) {
    *reg |= mask;
}

void clear_register_bits(volatile uint32_t *reg, uint32_t mask) {
    *reg &= ~mask;
}

void modify_register_field(volatile uint32_t *reg, uint32_t field_mask,
                         uint32_t field_value, int field_shift) {
    *reg = (*reg & ~field_mask) |
           ((field_value << field_shift) & field_mask);
}
```

### 5. Common Interview Questions

#### Counting Set Bits
```c
// Basic method
int count_set_bits(uint32_t n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

// Brian Kernighan's algorithm
int count_set_bits_efficient(uint32_t n) {
    int count = 0;
    while (n) {
        n = n & (n - 1);
        count++;
    }
    return count;
}
```

#### Power of 2 Check
```c
int is_power_of_2(uint32_t n) {
    return n > 0 && (n & (n - 1)) == 0;
}
```

#### Finding Single Number
```c
int find_single_number(int arr[], int size) {
    int result = 0;
    for (int i = 0; i < size; i++) {
        result ^= arr[i];
    }
    return result;
}
```

#### Bit Reversal
```c
uint32_t reverse_bits(uint32_t n) {
    uint32_t result = 0;
    for (int i = 0; i < 32; i++) {
        result = (result << 1) | (n & 1);
        n >>= 1;
    }
    return result;
}
```

### 6. Embedded Systems Applications

1. **GPIO Port Control**
   - Setting pin directions
   - Reading/writing pin states
   - Configuring pull-up/pull-down resistors

2. **ADC Configuration**
   - Setting resolution
   - Configuring reference voltage
   - Enabling/disabling ADC

3. **Interrupt Management**
   - Setting interrupt masks
   - Clearing interrupt flags
   - Checking interrupt status

## Best Practices

1. Use unsigned types for bit operations to avoid sign bit issues
2. Be careful with right shifts on signed numbers
3. Use parentheses to clarify operator precedence
4. Document bit positions and masks clearly
5. Consider portability when using bit operations
6. Use volatile keyword for hardware registers
7. Implement atomic operations for hardware control
8. Consider endianness in data packing/unpacking

## Common Pitfalls

1. Forgetting operator precedence
2. Confusing bitwise and logical operators
3. Not considering endianness
4. Ignoring sign bit in signed types
5. Assuming specific bit widths
6. Not using volatile for hardware registers
7. Non-atomic operations on hardware registers
8. Incorrect bit field alignment

## Key Takeaways

- Master set/clear/toggle operations for hardware control
- Understand masking for data extraction
- Practice register operations for embedded systems
- Know efficient algorithms for interviews
- Think hardware-first in C programming