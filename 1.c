#include <stdio.h>
#include <ctype.h>

void encrypt(char text[], int key) {
    char ch;
    for (int i = 0; text[i] != '\0'; ++i) {
        ch = text[i];

        // Encrypt uppercase letters
        if (isupper(ch)) {
            ch = (ch - 'A' + key) % 26 + 'A';
        }
        // Encrypt lowercase letters
        else if (islower(ch)) {
            ch = (ch - 'a' + key) % 26 + 'a';
        }
        text[i] = ch;
    }
}

int main() {
    char text[100];
    int key;

    // Get input from user
    printf("Enter a message to encrypt: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter the shift key (1-25): ");
    scanf("%d", &key);

    // Ensure the key is within the valid range
    if (key < 1 || key > 25) {
        printf("Invalid key! Please enter a key between 1 and 25.\n");
        return 1;
    }

    // Encrypt the text
    encrypt(text, key);

    // Display the encrypted message
    printf("Encrypted message: %s\n", text);

    return 0;
}
