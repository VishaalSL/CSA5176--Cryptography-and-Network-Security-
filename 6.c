#include <stdio.h>
#include <stdlib.h>

int mod(int a, int m) {
    return (a % m + m) % m;
}

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to find modular inverse of a under mod m
int modInverse(int a, int m) {
    a = mod(a, m);
    for (int x = 1; x < m; x++) {
        if (mod(a * x, m) == 1) {
            return x;
        }
    }
    return -1;  // Inverse doesn't exist
}

void breakAffineCipher(char mostFreq1, char mostFreq2) {
    // Assume:
    // Most frequent letter 'B' maps to 'E'
    // Second most frequent letter 'U' maps to 'T'
    int P_B = mostFreq1 - 'A'; // Position of B
    int P_U = mostFreq2 - 'A'; // Position of U
    int P_E = 'E' - 'A';        // Position of E
    int P_T = 'T' - 'A';        // Position of T

    // Loop over possible values of 'a' (1 to 25)
    for (int a = 1; a < 26; a++) {
        if (gcd(a, 26) == 1) { // a must be coprime to 26
            int b1 = mod(P_E - mod(a * P_B, 26), 26); // From B to E
            int b2 = mod(P_T - mod(a * P_U, 26), 26); // From U to T

            // Check if b1 and b2 are the same
            if (b1 == b2) {
                printf("Possible key found: a = %d, b = %d\n", a, b1);
            }
        }
    }
}

int main() {
    char mostFrequent1 = 'B'; // Most frequent letter
    char mostFrequent2 = 'U'; // Second most frequent letter

    breakAffineCipher(mostFrequent1, mostFrequent2);

    return 0;
}
