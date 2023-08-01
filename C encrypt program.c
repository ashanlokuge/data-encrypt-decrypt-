#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void encryptString(char str[], int key) {
    for (int i = 0; str[i] != '\0'; i++)
        str[i] = str[i] + key;
}

void decryptString(char str[], int key) {
    for (int i = 0; str[i] != '\0'; i++)
        str[i] = str[i] - key;
}

void encryptFile(const char *inputFileName, const char *outputFileName, int key) {
    FILE *inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        printf("\nError: Unable to open the input file.\n");
        return;
    }

    FILE *outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        printf("\nError: Unable to create the output file.\n");
        fclose(inputFile);
        return;
    }

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), inputFile) != NULL) {
        encryptString(buffer, key);
        fputs(buffer, outputFile);
    }

    fclose(inputFile);
    fclose(outputFile);
}

void decryptFile(const char *inputFileName, const char *outputFileName, int key) {
    FILE *inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        printf("\nError: Unable to open the input file.\n");
        return;
    }

    FILE *outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        printf("\nError: Unable to create the output file.\n");
        fclose(inputFile);
        return;
    }

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), inputFile) != NULL) {
        decryptString(buffer, key);
        fputs(buffer, outputFile);
    }

    fclose(inputFile);
    fclose(outputFile);
}

int isValidFileName(const char *fileName) {
    int len = strlen(fileName);
    if (len < 5) // At least 5 characters for ".txt"
        return 0;

    return (strcmp(fileName + len - 4, ".txt") == 0);
}

int main() {
    int key;
    char inputFileName[100];
    char outputFileName[100];

    printf("******** Welcome to the Ashan File Encrypt Decrypt Machine *********\n\n\n");

    // Prompt for input file name with validation
    do {
        printf("\nPlease enter the input file name (only txt files): ");
        scanf("%s", inputFileName);
        if (!isValidFileName(inputFileName)) {
            printf("\nInvalid file name. File name should have a .txt extension.\n");
        }
    } while (!isValidFileName(inputFileName));

    // Prompt for output file name for encryption with validation
    do {
        printf("\nPlease enter the output file name for encryption (only txt files): ");
        scanf("%s", outputFileName);
        if (!isValidFileName(outputFileName)) {
            printf("\nInvalid file name. File name should have a .txt extension.\n");
        }
    } while (!isValidFileName(outputFileName));

    printf("\nEnter the encryption key (integer): ");
    scanf("%d", &key);

    // Encrypt the file data
    encryptFile(inputFileName, outputFileName, key);
    printf("\nData from %s encrypted and written to %s.\n", inputFileName, outputFileName);

    // Prompt for output file name for decryption with validation
    do {
        printf("\nPlease enter the output file name for decryption: ");
        scanf("%s", outputFileName);
        if (!isValidFileName(outputFileName)) {
            printf("\nInvalid file name. File name should have a .txt extension.\n");
        }
    } while (!isValidFileName(outputFileName));

    // If input and output file names are the same, create a temporary file name
    char tempFileName[100];
    if (strcmp(inputFileName, outputFileName) == 0) {
        strcpy(tempFileName, "temp.txt");
    } else {
        strcpy(tempFileName, outputFileName);
    }

    // Decrypt the encrypted file data
    decryptFile(outputFileName, tempFileName, key);

    // If input and output file names are the same, delete the original encrypted file
    if (strcmp(inputFileName, outputFileName) == 0) {
        remove(outputFileName);
    }

    // Rename the temporary file to the output file name
    rename(tempFileName, inputFileName);

    printf("\nData from %s decrypted and written to %s.\n", outputFileName, inputFileName);

    return 0;
}
