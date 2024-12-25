#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function declarations
void fetchBinaryFromFile(char *filePath, char *binaryBuffer);
void binaryToHexConverter(char *binaryBuffer, char *hexBuffer);

int main() {
    char binaryBuffer[100];  // Buffer to hold binary input from file
    char hexBuffer[100];     // Buffer to store the resulting hexadecimal value


    fetchBinaryFromFile("binary.txt", binaryBuffer);


    binaryToHexConverter(binaryBuffer, hexBuffer);


    printf("Hexadecimal: %s\n", hexBuffer);

    return 0;
}

// Function to read binary input from a file
void fetchBinaryFromFile(char *filePath, char *binaryBuffer) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        printf("Error: Unable to open the file!\n");
        exit(1);
    }
    fgets(binaryBuffer, 100, file);
    fclose(file);
}

// Function to convert binary input to hexadecimal without adding leading zeros
void binaryToHexConverter(char *binaryBuffer, char *hexBuffer) {
    int length = strlen(binaryBuffer);
    int hexIndex = 0;

    // Trim any newline character at the end of the binary string
    if (binaryBuffer[length - 1] == '\n') {
        binaryBuffer[--length] = '\0';  // Reduce length to ignore the newline
    }

    // Start index for processing groups of four
    int start = (length % 4 == 0) ? 4 : length % 4;
    int i = 0;

    // Process the initial group if it's less than 4 bits
    if (start > 0) {
        int decimalValue = 0;
        for (i = 0; i < start; i++) {
            decimalValue = decimalValue * 2 + (binaryBuffer[i] - '0');
        }
        hexBuffer[hexIndex++] = (decimalValue < 10) ? ('0' + decimalValue) : ('A' + decimalValue - 10);
    }

    // Process remaining groups of 4 bits
    for (; i < length; i += 4) {
        int decimalValue = 0;
        for (int j = 0; j < 4; j++) {
            decimalValue = decimalValue * 2 + (binaryBuffer[i + j] - '0');
        }
        hexBuffer[hexIndex++] = (decimalValue < 10) ? ('0' + decimalValue) : ('A' + decimalValue - 10);
    }

    // Null-terminate the hexadecimal result string
    hexBuffer[hexIndex] = '\0';
}
