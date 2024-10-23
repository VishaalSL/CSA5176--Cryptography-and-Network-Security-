#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// A simple modulo operation to mimic signing in DSA (for demonstration)
int mod_exp(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

// Function to generate a random number
int generate_random_k() {
    return rand() % 100 + 1; // Generate random k between 1 and 100
}

// Function to "sign" a message
void sign_message(const char *message, int private_key, int mod, int *r, int *s) {
    int k = generate_random_k(); // Random k for each signature
    int hash = strlen(message);  // A simple hash (length of message, for demonstration)
    
    *r = mod_exp(k, 1, mod); // r = (g^k mod p) simulated
    *s = (hash + private_key * (*r)) * mod_exp(k, mod - 2, mod) % mod; // s = (hash + private_key * r) * k^-1 mod p
    printf("Random k used: %d\n", k);
}

int main() {
    srand(time(0)); // Seed for randomness
    
    const char *message = "Hello, World!";
    int private_key = 7;  // Simulated private key
    int mod = 101;        // A prime number for modulo (used as p)
    
    int r1, s1, r2, s2;
    
    // First signature
    printf("Signing the message for the first time:\n");
    sign_message(message, private_key, mod, &r1, &s1);
    printf("Signature 1: r = %d, s = %d\n", r1, s1);
    
    // Second signature (same message, different k)
    printf("\nSigning the message for the second time:\n");
    sign_message(message, private_key, mod, &r2, &s2);
    printf("Signature 2: r = %d, s = %d\n", r2, s2);
    
    // Show that the signatures are different
    if (r1 != r2 || s1 != s2) {
        printf("\nThe signatures are different because different k values were used.\n");
    } else {
        printf("\nThe signatures are identical (which should not happen in DSA).\n");
    }
    
    return 0;
}
