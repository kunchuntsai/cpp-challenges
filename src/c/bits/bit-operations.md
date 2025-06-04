# Bit Manipulation in C

This document covers fundamental bit manipulation concepts and techniques in C programming.

## Key Concepts

### 1. Bitwise Operators

- `&` (AND): Sets a bit to 1 only if both bits are 1
- `|` (OR): Sets a bit to 1 if either bit is 1
- `^` (XOR): Sets a bit to 1 if exactly one bit is 1
- `~` (NOT): Inverts all bits
- `<<` (Left Shift): Shifts bits left by specified amount
- `>>` (Right Shift): Shifts bits right by specified amount

### 2. Common Bit Operations

#### Setting a Bit
```c
num |= (1 << position);  // Sets bit at position to 1
```

#### Clearing a Bit
```c
num &= ~(1 << position);  // Sets bit at position to 0
```

#### Toggling a Bit
```c
num ^= (1 << position);  // Flips bit at position
```

#### Checking a Bit
```c
bit = (num >> position) & 1;  // Returns 1 if bit is set, 0 if not
```

### 3. Bit Masking Techniques

- Extracting specific bits using AND with a mask
- Setting specific bits using OR with a mask
- Clearing specific bits using AND with inverted mask
- Toggling specific bits using XOR with a mask

## Example Code

The `bit_operations.c` example demonstrates:

1. Basic bitwise operations
2. Setting, clearing, and toggling specific bits
3. Bit masking techniques
4. Bit counting
5. Bit shifting operations

## Common Use Cases

1. **Flags and Options**
   - Compact storage of boolean values
   - Efficient option handling

2. **Bit Fields**
   - Memory-efficient storage of small integers
   - Hardware register manipulation

3. **Bit Manipulation Algorithms**
   - Finding power of 2
   - Counting set bits
   - Checking if number is power of 2

## Best Practices

1. Use unsigned types for bit operations to avoid sign bit issues
2. Be careful with right shifts on signed numbers
3. Use parentheses to clarify operator precedence
4. Document bit positions and masks clearly
5. Consider portability when using bit operations

## Common Pitfalls

1. Forgetting operator precedence
2. Confusing bitwise and logical operators
3. Not considering endianness
4. Ignoring sign bit in signed types
5. Assuming specific bit widths 