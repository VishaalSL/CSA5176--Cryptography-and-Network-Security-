#include <stdio.h>
#include <stdint.h>

// Function to XOR two 8-bit blocks
uint8_t xorBlocks(uint8_t a, uint8_t b) {
    return a ^ b;
}

// S-DES key generation (subkeys K1 and K2)
void generateKeys(uint8_t key, uint8_t *K1, uint8_t *K2) {
    *K1 = (key & 0xF0) >> 1 | (key & 0x0F);
    *K2 = ((key & 0x0F) << 3) | ((key & 0xF0) >> 4);
}

// S-DES encryption function
uint8_t sdesEncrypt(uint8_t plaintext, uint8_t K1, uint8_t K2) {
    uint8_t temp = plaintext ^ K1; // XOR with K1
    temp = (temp << 2) | (temp >> 6); // Rotate left 2 bits
    return temp ^ K2; // XOR with K2
}

// S-DES decryption function
uint8_t sdesDecrypt(uint8_t ciphertext, uint8_t K1, uint8_t K2) {
    uint8_t temp = ciphertext ^ K2; // XOR with K2
    temp = (temp >> 2) | (temp << 6); // Rotate right 2 bits
    return temp ^ K1; // XOR with K1
}

// CBC mode encryption
void cbcEncrypt(uint8_t *plaintext, uint8_t *ciphertext, uint8_t iv, int size, uint8_t K1, uint8_t K2) {
    uint8_t previousBlock = iv;

    for (int i = 0; i < size; i++) {
        uint8_t xorResult = xorBlocks(plaintext[i], previousBlock);
        ciphertext[i] = sdesEncrypt(xorResult, K1, K2);
        previousBlock = ciphertext[i];
    }
}

// CBC mode decryption
void cbcDecrypt(uint8_t *ciphertext, uint8_t *decrypted, uint8_t iv, int size, uint8_t K1, uint8_t K2) {
    uint8_t previousBlock = iv;

    for (int i = 0; i < size; i++) {
        uint8_t decryptedBlock = sdesDecrypt(ciphertext[i], K1, K2);
        decrypted[i] = xorBlocks(decryptedBlock, previousBlock);
        previousBlock = ciphertext[i];
    }
}

int main() {
    // Test data
    uint8_t plaintext[] = {0x00, 0x01, 0x02, 0x03}; // Binary plaintext: 0000 0001 0010 0011
    uint8_t ciphertext[4], decrypted[4];
    uint8_t key = 0x1F; // Binary key: 01111 11101
    uint8_t iv = 0xAA;  // Initialization vector: 1010 1010
    uint8_t K1, K2;

    // Generate subkeys
    generateKeys(key, &K1, &K2);

    // Encrypt using CBC mode
    cbcEncrypt(plaintext, ciphertext, iv, 4, K1, K2);

    // Print ciphertext
    printf("Ciphertext:\n");
    for (int i = 0; i < 4; i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");

    // Decrypt using CBC mode
    cbcDecrypt(ciphertext, decrypted, iv, 4, K1, K2);

    // Print decrypted plaintext
    printf("Decrypted Plaintext:\n");
    for (int i = 0; i < 4; i++) {
        printf("%02X ", decrypted[i]);
    }
    printf("\n");

    return 0;
}
