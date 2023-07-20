#include "encryption.h"

#include <stdio.h> /*printf(), scanf(), fprintf(), fscanf(), getchar(), fopen,
                    fclose(), fgetc()*/
#include <stdlib.h>/*malloc(), free(), atoi(), fseek(), ftell() */
#include <string.h>/*strcpy(), strlen() */

void encryptFile(char filename[]) {
    int key;
    char fname[50];
    strcpy(fname, filename);
    char input[3500];
    int isValidInput = 0; 

    while (!isValidInput) { /* while loop used to ensure correct input */
        printf("Enter a key: ");
        if (scanf("%d", &key) == 1) {
            isValidInput = 1; /* ends while loop */
        } else {
            printf("Invalid input. Please enter a valid integer.\n");
            while (getchar() != '\n'); /* clears input */
        }
    }
    while (getchar() != '\n'); 

    char *fileInputP = readFile(fname); /* reads file */
    strcpy(input, fileInputP); /* copies file into input string */
    free(fileInputP); /* memory cleared to prevent data leak */

    int length = strlen(input); 
    char output[length + 1];

    /* passes input through the encryption algorithm multiple times */
    encrypting(input, output, key);
    encrypting(output, output, key);
    encrypting(output, output, key);
    encrypting(output, output, key);
    encrypting(output, output, key);
    encrypting(output, output, key);
    writeFile(output, fname);
}

void decryptFile(char filename[]) {
    int key;
    char fname[50];
    strcpy(fname, filename);
    char output[3500];
    int isValidInput = 0;

    while (!isValidInput) { /* while loop used to ensure correct input */
        printf("Enter a key: ");
        if (scanf("%d", &key) == 1) {
            isValidInput = 1; /* ends while loop */
        } else {
            printf("Invalid input. Please enter a valid integer.\n");
            while (getchar() != '\n'); /* clears input */
        }
    }
    while (getchar() != '\n');

    char *fileInputP = readFile(fname); /* reads file */
    strcpy(output, fileInputP); /* copies file into output string */
    //free(fileInputP); /* memory cleared to prevent data leak */

    int length = strlen(output);
    char decrypted[length + 1];

    /* encrypted text is passed through decryption algorith */
    decrypting(output, decrypted, key);
    decrypting(decrypted, decrypted, key);
    decrypting(decrypted, decrypted, key);
    decrypting(decrypted, decrypted, key);
    decrypting(decrypted, decrypted, key);
    decrypting(decrypted, decrypted, key);
    writeFile(decrypted, fname);
}

void encrypting(char input[], char output[], int key) {
    int length = strlen(input);
    int i;

    for (i = 0; i < length; i++) {
        if (input[i] == '\n') {
            output[i] = '\n';
        } else {
            /* 32 is taked away from the input and modulu is used to keep the
            characters within the printable range */
            output[i] = input[i] - 32;
            output[i] = (output[i] + key) % 94;
            /* 32 is added back so the output is printable */
            output[i] = output[i] + 32;

            /*Prints the current key and the loop counter for debugging */
            #ifdef DEBUG
                printf("DEBUG: key = %d\n", key);
                printf("DEBUG: i = %d", i);
            #endif

            key++; /* increased key so that cipher rotates */
            if (key > 94) {
                key = key - 94; /* ensures key does not grow too large */
            }
        }
    }

    output[i] = '\0'; /* null character added to end of output */
}

void decrypting(char output[], char decrypted[], int key) {
    int length = strlen(output);
    int i;

    for (i = 0; i < length; i++) {
        if (output[i] == '\n') {
            decrypted[i] = '\n';
        } else {
            decrypted[i] = output[i] - key;
            /* ensures decrypted text falls within the correct range */
            while (decrypted[i] < 32) {
                decrypted[i] = decrypted[i] + 94;
                
            }

            #ifdef DEBUG
                printf("DEBUG: key = %d\n", key);
                printf("DEBUG: i = %d", i);
            #endif

            key++; /* key is increased to reverse encryption. */
            if (key > 94) {
                key = key - 94; /* ensures key does not grow too large */
            }
        }
    }

    decrypted[i] = '\0'; /* null character added */
}

void writeFile(char input[], char *fname) {
    FILE *fp = fopen(fname, "w");
    if (fp == NULL) { /*prints error message if file fails to open*/
        printf("Error opening file.\n");
        return;
    }

    /* prints string into a txt file */
    fprintf(fp, "%s", input);
    fclose(fp);
}

char *readFile(char *fname) {
    FILE *fp = fopen(fname, "r");
    if (fp == NULL) {
        printf("Error reading file\n");
        return NULL;
    }

    /* file pointer is used to determine the size of file */
    fseek(fp, 0, SEEK_END);
    int length = ftell(fp);
    fseek(fp, 0, SEEK_SET);  

    /* allocates memory to store content as string */
    char *string = malloc((length+1) *sizeof(char));

    char c; 
    int i =0;

    /* characters are read one by one from the file and stored in string */    
    while ((c = fgetc(fp)) != EOF){
        string[i] = c;
        i++;
    }
    string[i] = '\0'; /* null characters added to terminate string */

    fclose(fp);

    return string;
}

void encryptPassword(void) {
    int key = 5;
    char input[3500];

    FILE *fp = fopen("password.txt", "r");
    if (fp == NULL) {
        printf("Error reading file\n");
        return;
    }

    /* file pointer is used to determine the size of file */
    fseek(fp, 0, SEEK_END);
    int passwordLength = ftell(fp);
    fseek(fp, 0, SEEK_SET);  

    /* allocates memory to store content as string */
    char *string = malloc((passwordLength+1) *sizeof(char));

    char c; 
    int i =0;

    /* characters are read one by one from the file and stored in string */    
    while ((c = fgetc(fp)) != EOF){
        string[i] = c;
        i++;
    }
    string[i] = '\0'; /* null characters added to terminate string */

    fclose(fp);

    strcpy(input, string); /* copies file into input string */
    free(string); /* memory cleared to prevent data leak */

    int length = strlen(input); 
    char output[length + 1];

    /* passes input through the encryption algorithm multiple times */
    encrypting(input, output, key);
    encrypting(output, output, key);
    encrypting(output, output, key);
    encrypting(output, output, key);
    encrypting(output, output, key);
    encrypting(output, output, key);

    FILE *fOutputp = fopen("password.txt", "w");
    if (fp == NULL) { /*prints error message if file fails to open*/
        printf("Error opening file.\n");
        return;
    }

    /* prints string into a txt file */
    fprintf(fOutputp, "%s", output);
    fclose(fOutputp);
}

int decryptPassword(void) {
    int key = 5;
    char output[3500];

    /* opens files for reading */
    FILE *fp = fopen("password.txt", "r");
    if (fp == NULL) {
        printf("Error reading file\n");
        return 0;
    }

    /* file pointer is used to determine the size of file */
    fseek(fp, 0, SEEK_END);
    int passwordLength = ftell(fp);
    fseek(fp, 0, SEEK_SET);  

    /* allocates memory to store content as string */
    char *string = malloc((passwordLength+1) *sizeof(char));

    char c; 
    int i =0;

    /* characters are read one by one from the file and stored in string */    
    while ((c = fgetc(fp)) != EOF){
        string[i] = c;
        i++;
    }
    string[i] = '\0'; /* null characters added to terminate string */

    fclose(fp);

    strcpy(output, string); /* copies file into output string */
    free(string); /* memory cleared to prevent data leak */

    int length = strlen(output);
    char decrypted[length + 1];

    /* encrypted text is passed through decryption algorith */
   decrypting(output, decrypted, key);
    decrypting(decrypted, decrypted, key);
    decrypting(decrypted, decrypted, key);
    decrypting(decrypted, decrypted, key);
    decrypting(decrypted, decrypted, key);
    decrypting(decrypted, decrypted, key);

    int decryptPassword = atoi(decrypted);
    return decryptPassword;

}

