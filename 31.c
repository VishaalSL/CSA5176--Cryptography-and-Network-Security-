#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Constants for subkey generation
#define BLOCK_SIZE_64 64
#define BLOCK_SIZE_128 128

// Rb values for different block sizes
#define Rb_64 0x1B
#define Rb_128 0x87

// Function to left shift an array of bytes
void left_shift(uint8_t *input, uint8_t *output, int length) {
    uint8_t carry = 0;
    for (int i = length - 1; i >= 0; i--) {
        output[i] = (input[i] << 1) | carry;
        carry = (input[i] & 0x80) ? 1 : 0;
    }
}

// Function to XOR with Rb if MSB is set
void xor_with_rb(uint8_t *input, int length, uint8_t Rb) {
    if (input[0] & 0x80) {
        input[length - 1] ^= Rb;
    }
}

// Function to generate the CMAC subkeys
void generate_subkeys(uint8_t *key, int block_size) {
    int length = block_size / 8;
    uint8_t L[length], K1[length], K2[length];
    uint8_t Rb = (block_size == BLOCK_SIZE_64) ? Rb_64 : Rb_128;

    // Step 1: Apply block cipher to the zero block (simulate here)
    memset(L, 0, length);
    // Simulating encryption of L (normally done with a block cipher)
    memcpy(L, key, length);

    // Step 2: Derive K1
    left_shift(L, K1, length);
    xor_with_rb(K1, length, Rb);

    // Step 3: Derive K2
    left_shift(K1, K2, length);
    xor_with_rb(K2, length, Rb);

    // Output subkeys
    printf("K1: ");
    for (int i = 0; i < length; i++) {
        printf("%02X ", K1[i]);
    }
    printf("\n");

    printf("K2: ");
    for (int i = 0; i < length; i++) {
        printf("%02X ", K2[i]);
    }
    printf("\n");
}

int main() {
    // Example key (should be replaced with actual key in real application)
    uint8_t key_128[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                           0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};

    printf("Generating subkeys for 128-bit block size:\n");
    generate_subkeys(key_128, BLOCK_SIZE_128);

    return 0;
}
