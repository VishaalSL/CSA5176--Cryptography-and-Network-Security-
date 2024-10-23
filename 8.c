#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function to create cipher alphabet from the keyword
void createCipherAlphabet(char* keyword, char* cipherAlphabet) {
    int used[ALPHABET_SIZE] = {0};  // To track used letters
    int index = 0;
    
    // Add unique letters from the keyword to the cipher alphabet
    for (int i = 0; i < strlen(keyword); i++) {
        char c = toupper(keyword[i]);  // Convert to uppercase
        if (isalpha(c) && !used[c - 'A']) {  // Check if it's a letter and not used
            cipherAlphabet[index++] = c;
            used[c - 'A'] = 1;  // Mark letter as used
        }
    }
    
    // Add remaining letters in normal order
    for (char c = 'A'; c <= 'Z'; c++) {
        if (!used[c - 'A']) {
            cipherAlphabet[index++] = c;  // Add unused letters
        }
    }
    
    cipherAlphabet[index] = '\0';  // Null terminate the cipher alphabet
}

// Function to encrypt plaintext using the cipher alphabet
void encrypt(char* plaintext, char* cipherAlphabet, char* encryptedText) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        char c = toupper(plaintext[i]);  // Convert to uppercase
        if (isalpha(c)) {
            int pos = c - 'A';  // Get position in alphabet
            encryptedText[i] = cipherAlphabet[pos];  // Substitute
        } else {
            encryptedText[i] = plaintext[i];  // Non-alphabetic characters unchanged
        }
    }
    encryptedText[strlen(plaintext)] = '\0';  // Null terminate the encrypted text
}

int main() {
    char keyword[100], plaintext[100], cipherAlphabet[ALPHABET_SIZE + 1], encryptedText[100];

    // Input the keyword
    printf("Enter the keyword: ");
    scanf("%s", keyword);

    // Create the cipher alphabet based on the keyword
    createCipherAlphabet(keyword, cipherAlphabet);
    printf("Cipher Alphabet: %s\n", cipherAlphabet);

    // Input the plaintext
    printf("Enter the plaintext: ");
    scanf(" %[^\n]", plaintext);  // Read line including spaces

    // Encrypt the plaintext
    encrypt(plaintext, cipherAlphabet, encryptedText);
    printf("Encrypted Text: %s\n", encryptedText);

    return 0;
}
