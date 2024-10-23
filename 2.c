#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Function to encrypt using the monoalphabetic substitution cipher
void encrypt(char text[], char key[]) {
    char ch;
    for (int i = 0; text[i] != '\0'; ++i) {
        ch = text[i];

        // Encrypt uppercase letters
        if (isupper(ch)) {
            text[i] = toupper(key[ch - 'A']);
        }
        // Encrypt lowercase letters
        else if (islower(ch)) {
            text[i] = tolower(key[ch - 'a']);
        }
    }
}

int main() {
    char text[100];
    char key[ALPHABET_SIZE + 1];  // Cipher key should be a permutation of 26 letters
    char alphabet[ALPHABET_SIZE + 1] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // Get input from user
    printf("Enter a message to encrypt: ");
    fgets(text, sizeof(text), stdin);

    // Get the cipher key from the user
    printf("Enter the 26-letter substitution key (cipher alphabet): ");
    scanf("%s", key);

    // Validate that the key has exactly 26 unique letters
    if (strlen(key) != ALPHABET_SIZE) {
        printf("Invalid key! The key must contain exactly 26 letters.\n");
        return 1;
    }

    // Encrypt the text
    encrypt(text, key);

    // Display the encrypted message
    printf("Encrypted message: %s\n", text);

    return 0;
}
