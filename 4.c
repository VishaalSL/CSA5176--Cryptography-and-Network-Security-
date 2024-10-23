#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to generate the repeated key for the given plaintext
void generate_key(const char *plaintext, const char *keyword, char *key) {
    int text_len = strlen(plaintext);
    int key_len = strlen(keyword);
    int i, j;

    // Repeat the keyword to match the length of the plaintext
    for (i = 0, j = 0; i < text_len; i++) {
        if (isalpha(plaintext[i])) {
            key[i] = toupper(keyword[j % key_len]);
            j++;
        } else {
            key[i] = plaintext[i];  // Keep non-alphabet characters unchanged
        }
    }
    key[text_len] = '\0';  // Null-terminate the key
}

// Function to encrypt the plaintext using the generated key
void encrypt(const char *plaintext, const char *key, char *ciphertext) {
    int text_len = strlen(plaintext);
    int shift, i;

    for (i = 0; i < text_len; i++) {
        if (isalpha(plaintext[i])) {
            // Calculate the shift for each letter based on the key
            shift = toupper(key[i]) - 'A';

            if (isupper(plaintext[i])) {
                ciphertext[i] = (plaintext[i] - 'A' + shift) % 26 + 'A';
            } else if (islower(plaintext[i])) {
                ciphertext[i] = (plaintext[i] - 'a' + shift) % 26 + 'a';
            }
        } else {
            // Non-alphabet characters are added directly to the ciphertext
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[text_len] = '\0';  // Null-terminate the ciphertext
}

int main() {
    char plaintext[100], keyword[100], key[100], ciphertext[100];

    // Input the plaintext and keyword
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';  // Remove the trailing newline

    printf("Enter the keyword: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0';  // Remove the trailing newline

    // Generate the key by repeating the keyword
    generate_key(plaintext, keyword, key);

    // Encrypt the plaintext using the Vigenère cipher
    encrypt(plaintext, key, ciphertext);

    // Output the ciphertext
    printf("Encrypted message: %s\n", ciphertext);

    return 0;
}
