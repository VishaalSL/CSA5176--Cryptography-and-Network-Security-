#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 16  // Assuming a block size of 16 bytes (128 bits)

// Simple XOR function for two blocks
void xorBlocks(uint8_t *out, uint8_t *in1, uint8_t *in2, size_t length) {
    for (size_t i = 0; i < length; i++) {
        out[i] = in1[i] ^ in2[i];
    }
}

// A mock CBC-MAC function, here just to simulate the behavior
void CBC_MAC(uint8_t *key, uint8_t *message, uint8_t *mac, size_t length) {
    // For simplicity, we assume the key is XORed directly to simulate CBC-MAC
    // In real CBC-MAC, we'd use block cipher encryption (e.g., AES)
    xorBlocks(mac, key, message, length);  // Simulate encryption (XOR here)
}

// Helper function to print blocks
void printBlock(uint8_t *block, size_t length) {
    for (size_t i = 0; i < length; i++) {
        printf("%02x", block[i]);
    }
    printf("\n");
}

int main() {
    uint8_t key[BLOCK_SIZE] = {0x00};     // CBC-MAC key (initialized to 0 for simplicity)
    uint8_t message[BLOCK_SIZE] = {0x10}; // One-block message X (just an example)
    uint8_t mac[BLOCK_SIZE];              // To store the MAC result

    // Step 1: Compute CBC-MAC for the one-block message X
    CBC_MAC(key, message, mac, BLOCK_SIZE);
    printf("CBC-MAC for one-block message X: ");
    printBlock(mac, BLOCK_SIZE);

    // Step 2: Compute CBC-MAC for two-block message X || (X XOR T)
    uint8_t messageXorMac[BLOCK_SIZE];
    xorBlocks(messageXorMac, message, mac, BLOCK_SIZE);  // X XOR T
    uint8_t twoBlockMessage[2 * BLOCK_SIZE];

    // Concatenate X and (X XOR T) to form the two-block message
    memcpy(twoBlockMessage, message, BLOCK_SIZE);          // Copy X
    memcpy(twoBlockMessage + BLOCK_SIZE, messageXorMac, BLOCK_SIZE);  // Copy (X XOR T)

    // Step 3: Compute CBC-MAC for the two-block message X || (X XOR T)
    CBC_MAC(key, twoBlockMessage, mac, 2 * BLOCK_SIZE);
    printf("CBC-MAC for two-block message X || (X XOR T): ");
    printBlock(mac, BLOCK_SIZE);

    return 0;
}
