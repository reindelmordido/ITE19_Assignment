#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readBinaryFromFile(char *fileName, char *binaryData);
void convertBinaryToHex(char *binaryData, char *hexData);

int main() {
    char binaryData[100];
    char hexData[100];

    readBinaryFromFile("binary.txt", binaryData);
    convertBinaryToHex(binaryData, hexData);

    printf("Hexadecimal: %s\n", hexData);

    return 0;
}

void readBinaryFromFile(char *fileName, char *binaryData) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error: Unable to open the file!\n");
        exit(1);
    }
    fgets(binaryData, 100, file);
    fclose(file);
}

void convertBinaryToHex(char *binaryData, char *hexData) {
    int length = strlen(binaryData);
    int hexPosition = 0;

    if (binaryData[length - 1] == '\n') {
        binaryData[--length] = '\0';
    }

    int initialGroup = (length % 4 == 0) ? 4 : length % 4;
    int i = 0;

    if (initialGroup > 0) {
        int decimalValue = 0;
        for (i = 0; i < initialGroup; i++) {
            decimalValue = decimalValue * 2 + (binaryData[i] - '0');
        }
        hexData[hexPosition++] = (decimalValue < 10) ? ('0' + decimalValue) : ('A' + decimalValue - 10);
    }

    for (; i < length; i += 4) {
        int decimalValue = 0;
        for (int j = 0; j < 4; j++) {
            decimalValue = decimalValue * 2 + (binaryData[i + j] - '0');
        }
        hexData[hexPosition++] = (decimalValue < 10) ? ('0' + decimalValue) : ('A' + decimalValue - 10);
    }

    hexData[hexPosition] = '\0';
}
