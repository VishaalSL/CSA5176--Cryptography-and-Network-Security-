#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 100

// Function to convert character to number (A=0, B=1, ..., Z=25)
int charToNum(char c) {
    return toupper(c) - 'A';
}

// Function to convert number to character (0=A, 1=B, ..., 25=Z)
char numToChar(int num) {
    return num + 'A';
}

// Hill cipher encryption function
void encryptHill(char *text, int *keyMatrix, int keySize) {
    int i, j, k, textLen = strlen(text), encrypted[MAX_LEN] = {0};

    for (i = 0; i < textLen; i += keySize) {
        for (j = 0; j < keySize; j++) {
            int sum = 0;
            for (k = 0; k < keySize; k++) {
                sum += keyMatrix[j * keySize + k] * charToNum(text[i + k]);
            }
            encrypted[i + j] = sum % 26;
        }
    }

    for (i = 0; i < textLen; i++) {
        text[i] = numToChar(encrypted[i]);
    }
}

// Main function
int main() {
    char plaintext[MAX_LEN] = "MEET ME AT THE USUAL PLACE AT TEN RATHER THAN EIGHT OCLOCK";
    int keySize = 2;  // The key matrix is 2x2
    int keyMatrix[] = {9, 4, 5, 7};  // Key matrix provided in the question
    
    // Preprocessing the plaintext: remove spaces and convert to uppercase
    char processedText[MAX_LEN] = {0};
    int index = 0;

    for (int i = 0; i < strlen(plaintext); i++) {
        if (isalpha(plaintext[i])) {  // Only consider alphabetic characters
            processedText[index++] = toupper(plaintext[i]);
        }
    }
    processedText[index] = '\0';  // Null-terminate the processed text

    int textLen = strlen(processedText);

    // Padding the text if necessary
    int padding = keySize - (textLen % keySize);
    if (padding < keySize) {
        memset(processedText + textLen, 'X', padding);
        processedText[textLen + padding] = '\0';
    }

    // Encrypt the processed text
    encryptHill(processedText, keyMatrix, keySize);

    // Output the encrypted text
    printf("Encrypted text: %s\n", processedText);

    return 0;
}
