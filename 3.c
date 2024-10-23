#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

char matrix[SIZE][SIZE];
int positions[26];  // To store positions of letters in the matrix

// Function to remove duplicates from the keyword
void remove_duplicates(char key[], char new_key[]) {
    int len = strlen(key);
    int index = 0;

    for (int i = 0; i < len; i++) {
        char ch = toupper(key[i]);
        if (ch == 'J') ch = 'I';  // Treat 'I' and 'J' as the same letter

        if (positions[ch - 'A'] == -1 && isalpha(ch)) {
            new_key[index++] = ch;
            positions[ch - 'A'] = 1;  // Mark the letter as used
        }
    }
    new_key[index] = '\0';  // Null terminate the new key
}

// Function to create the 5x5 Playfair matrix
void create_matrix(char key[]) {
    char alphabet[] = "ABCDEFGHIKLMNOPQRSTUVWXYZ";  // I/J combined
    char new_key[26];  // Final keyword without duplicates
    int key_index = 0;
    int alphabet_index = 0;

    // Remove duplicates from the keyword
    remove_duplicates(key, new_key);

    // Fill the matrix with the keyword first
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (key_index < strlen(new_key)) {
                matrix[i][j] = new_key[key_index++];
            } else {
                // Fill remaining with the rest of the alphabet
                while (positions[alphabet[alphabet_index] - 'A'] != -1) {
                    alphabet_index++;
                }
                matrix[i][j] = alphabet[alphabet_index++];
            }
        }
    }
}

// Function to find the position of a letter in the matrix
void find_position(char ch, int *row, int *col) {
    if (ch == 'J') ch = 'I';  // Treat 'I' and 'J' as the same letter

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to encrypt the digraph
void encrypt_pair(char *first, char *second) {
    int row1, col1, row2, col2;

    find_position(*first, &row1, &col1);
    find_position(*second, &row2, &col2);

    if (row1 == row2) {
        // Same row: shift to the right
        *first = matrix[row1][(col1 + 1) % SIZE];
        *second = matrix[row2][(col2 + 1) % SIZE];
    } else if (col1 == col2) {
        // Same column: shift downward
        *first = matrix[(row1 + 1) % SIZE][col1];
        *second = matrix[(row2 + 1) % SIZE][col2];
    } else {
        // Rectangle rule: swap columns
        *first = matrix[row1][col2];
        *second = matrix[row2][col1];
    }
}

// Function to prepare the plaintext by making digraphs
void prepare_text(char text[], char new_text[]) {
    int len = strlen(text);
    int index = 0;

    for (int i = 0; i < len; i++) {
        char ch = toupper(text[i]);
        if (!isalpha(ch)) continue;  // Ignore non-alphabet characters

        if (index > 0 && new_text[index - 1] == ch) {
            // If two consecutive letters are the same, insert 'X'
            new_text[index++] = 'X';
        }

        new_text[index++] = ch;
    }

    // If the length is odd, add 'X' at the end
    if (index % 2 != 0) {
        new_text[index++] = 'X';
    }
    new_text[index] = '\0';  // Null terminate
}

// Function to encrypt the entire plaintext
void encrypt_text(char text[]) {
    char prepared_text[100];
    prepare_text(text, prepared_text);

    for (int i = 0; i < strlen(prepared_text); i += 2) {
        encrypt_pair(&prepared_text[i], &prepared_text[i + 1]);
    }

    printf("Encrypted message: %s\n", prepared_text);
}

int main() {
    char keyword[26];
    char plaintext[100];

    // Initialize positions array to -1 (unmarked)
    for (int i = 0; i < 26; i++) positions[i] = -1;

    // Get keyword and plaintext from the user
    printf("Enter the keyword: ");
    scanf("%s", keyword);

    printf("Enter the plaintext: ");
    scanf("%s", plaintext);

    // Create the Playfair matrix
    create_matrix(keyword);

    // Display the matrix (optional, for debugging)
    printf("\nPlayfair matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }

    // Encrypt the plaintext
    encrypt_text(plaintext);

    return 0;
}
