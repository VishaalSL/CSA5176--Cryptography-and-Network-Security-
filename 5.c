#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to calculate gcd of two numbers
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to find modular inverse of a under mod 26
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;  // Inverse doesn't exist if a is not coprime with 26
}

// Function to encrypt using Affine cipher
char affineEncrypt(char plaintext, int a, int b) {
    if (plaintext >= 'A' && plaintext <= 'Z') {
        int p = plaintext - 'A';  // Convert to 0-25 range
        int c = (a * p + b) % 26; // Affine encryption formula
        return (c + 'A');         // Convert back to letter
    }
    return plaintext;  // Return non-alphabetic characters unchanged
}

// Function to decrypt using Affine cipher
char affineDecrypt(char ciphertext, int a, int b) {
    if (ciphertext >= 'A' && ciphertext <= 'Z') {
        int c = ciphertext - 'A';  // Convert to 0-25 range
        int a_inv = modInverse(a, 26);  // Find modular inverse of a
        if (a_inv == -1) {
            printf("Inverse doesn't exist for a = %d\n", a);
            exit(1);
        }
        int p = (a_inv * (c - b + 26)) % 26; // Affine decryption formula
        return (p + 'A');  // Convert back to letter
    }
    return ciphertext;  // Return non-alphabetic characters unchanged
}

int main() {
    char plaintext[100], ciphertext[100];
    int a, b;

    // Input values for 'a' and 'b'
    printf("Enter values for a and b (for the cipher C = (a * P + b) mod 26): ");
    scanf("%d %d", &a, &b);

    // Ensure that 'a' and 26 are coprime
    if (gcd(a, 26) != 1) {
        printf("'a' must be coprime with 26. Invalid value for a.\n");
        return 1;
    }

    // Input plaintext
    printf("Enter the plaintext: ");
    scanf("%s", plaintext);

    // Encrypt the plaintext
    for (int i = 0; plaintext[i] != '\0'; i++) {
        ciphertext[i] = affineEncrypt(plaintext[i], a, b);
    }
    ciphertext[strlen(plaintext)] = '\0';  // Null terminate the ciphertext

    // Display encrypted text
    printf("Encrypted message: %s\n", ciphertext);

    // Decrypt the ciphertext
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        plaintext[i] = affineDecrypt(ciphertext[i], a, b);
    }
    plaintext[strlen(ciphertext)] = '\0';  // Null terminate the plaintext

    // Display decrypted text
    printf("Decrypted message: %s\n", plaintext);

    return 0;
}
