/* 
Group 4:

Connor Mawer: 13900372
Oliver Shim: 24563619
Mengjing Cao: 13744622
Andre Ibrahim: 13532876

COMPILING INSTRUCTIONS:

make
./program
make clean 

Who did what:
Connor, Oliver (encryption.c, encryption.h)
Mengjing, Andre (Huffman.c, Huffman.h)
Connor, Oliver, Mengjing(main.c)
Mengjing (makefile)

*/
#include <string.h>/*strcpy(), strcat()*/
#include <stdio.h> /*remove(), printf(), scanf(),fopen(),fclose(),fprintf(), getchar()*/
#include <stdlib.h> /*malloc()*/
#include "Huffman.h"
#include "encryption.h"

/* #define DEBUG */

/*FUNCTION DEFINITIONS*/
int warning(void);
void printMenu(void); 
void tutorial(void);
void deleteFile();
void compression_decompression(const char *input_file, int i);


int main (void){
    int i; /*A mode selection variable for the switch statement*/
    int isFile = 0;
    int password = decryptPassword();
    int passwordCheck;
    int validPassword = 0;

    /*A while loop that continues to operate the program as long as the user
    has not chosen to exit the program. */
    while (i != 6){
        printMenu(); /*Prints the menu*/
        printf("Enter your choice(1-5):");
        scanf("%d", &i); /* reads the user selection and stores it */

        /* A switch statement to execute the appropriate functions based
        on the users selection */
        switch (i){
        
        case 1: /*Add a file mode*/
            printf("Add file\n");
            printf("Please enter a filename:");
            char filename[100];
            scanf("%s", filename); /*Stores the user entered filename*/
            FILE *file = fopen(filename, "r");
            if (file == NULL) {
                printf("Failed, please make sure the file name is correct");
                break;
            }
            isFile = 1;

            /* Ask user if they want to delete copy of the original */ 
            printf("Do you want to make a copy of the selected file?\n");
            printf("NOTE: The copy is not protected by our encryption.\n");
            printf("Press 'Y' to make a copy or 'C' to cancel.\n");
            char selection;
            scanf(" %c", &selection);

            if((selection == 'Y') || (selection == 'y')){
                /* Copy the original file */
                char new_name[10] = "Copy_";  /* The words we add */
                char new_filename[100];       /* The new name */
                
                strcpy(new_filename, new_name);
                strcat(new_filename, filename);

                FILE *new_file = fopen(new_filename, "w");
                if (new_file == NULL) {
                    printf("Error creating file %s\n", new_filename);
                    break;
                }
                char buffer[1024];
                size_t bytes_read;
                while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
                    fwrite(buffer, 1, bytes_read, new_file);
                }

                fclose(new_file);

                printf("Copy the original file successfully\n");
            }

            else if((selection == 'C') || (selection == 'c')){
                break;
            }
            break;
        /*Delete File */
        case 2:
            printf("Delete file\n");
            /* Runs the standardised warnign fucntion and returns the users
            selection.*/
            int y = warning(); 
            if (y == 1){
               deleteFile(); /*Executed the delete file function*/
            } 
            else if (y == 2){
                break; /*Breaks and returns teh user to the menu.*/
            }  
            break;

        /*Encryption and Compression*/
        case 3:
        /*If no file has been added to the program the operation is stopped, 
        the user is informed and they are returned to the menue */
            if (isFile == 0){
                printf("\nNO FILE ADDED\nPlease add a file before proceeding");
                break; 
            }

            else{
                printf("Encryption and Compression\n\n");
                y = warning(); /*Standard warning function*/

                if (y == 1){
                    while(1){
                        /* password is scanned checked for numerical input */
                        printf("Set a 4 digit password(between 1000 and 9999):");
                        validPassword = scanf("%d", &password);

                            #ifdef DEBUG
                                printf("\n DEBUG: entered password = %d\n", password);
                                /*Debug mode that prints the stored password*/
                            #endif

            /*A series of if/else if statements to check if the password entered */
            /*meets the requirements */
                        if (validPassword == 0){
                            while (getchar() != '\n');
                            printf("\nInvalid Password\nEnter Numerical Characters Only\n");
                        }

                        else if(password < 1000 || password > 9999){
                            printf("\nPassword is Invalid\n\n");
                        }
                        else{

                            /*password is stored into a file so that i can
                            be encrypted */
                            FILE *passfile;
                            passfile = fopen("password.txt", "w");
    
                            if (passfile == NULL) {
                            printf("Error opening file!\n");
                
                            }
    
                            fprintf(passfile, "%d", password);
                            fclose(passfile);

                    /*A function that encrypts the password and stores it */
                            encryptPassword(); 
                            break;
                        }
                    }

                /*Encrypts the chosen file */   
                encryptFile(filename);
                scanf("nothing");
                /*Execute Compression*/
                compression_decompression (filename, 0);
                } 

                else if (y == 2){
                    break; /* Returns the user to the menu*/
                }  
                break;
            }    
        case 4:
            printf("Decompression and Decryption\n\n");
            y = warning(); /*Standard warning function */
            if (y == 1){
               while(1){
                    /* Password is read from user input*/
                    validPassword = 0;
                    printf("Enter password (between 1000 and 9999):");
                    validPassword = scanf("%d", &passwordCheck);
                    
                    /*ensures password is of a numerical value */
                    if(validPassword == 0){
                        while (getchar() != '\n');
                        printf("\nInvalid Password\nEnter Numerical Characters\
                         Only\n");
                    }

                    #ifdef DEBUG
                        printf("DEBUG: validPassword == %d", validPassword);
                    #endif
                    /* checks if entered password matches stored password */
                    else if(passwordCheck == password){
                        break;
                    }
                    else{
                        printf("Invalid Password. Try Again\n");
                    }

                } 
                while (1) {
                    printf("Enter the filename to decompress: ");
                    scanf("%s", filename);
                    FILE *file = fopen(filename, "r");
                    
                    if (file == NULL) {
                        printf("Failed, please make sure the file name "
                        "is correct.\n");
                    } else {
                        /* If the file exists, perform subsequent operations */
                        #ifdef DEBUG
                            printf("File found! Processing...\n");
                        #endif
                        fclose(file);
                        break;
                    }
                }
                /* The filename is test.bin */
                compression_decompression (filename, 1);
                fclose(file);
                /* The filename back to test.txt */
                /* renew the name of filename to test.txt */
                while (1) {
                    printf("Enter the filename to decrypt: ");
                    scanf("%s", filename);
                    FILE *file = fopen(filename, "r");

                    if (file == NULL) {
                        printf("Failed, please make sure the file name "
                        "is correct.\n");
                    } else {
                        /* If the file exists, perform subsequent operations */
                        #ifdef DEBUG
                            printf("File found! Processing...\n");
                        #endif
                        fclose(file);
                        break;
                    }
                }
                decryptFile(filename);
            }

            else if (y == 2){
                /* return to menu selection */
                break;
            } 
            
            break;
        case 5:
            printf("Tutorial\n");
            tutorial(); /* Executes the Tutorial function */
            break;
        case 6:
            printf("Exit the program\n");
            break;
        default:
            /*informs the user if their input is incorrect.  */
            printf("The input should be between 1 and 6\n");
        }
    }
    return 0;
}

void printMenu(void){ /* prints a menu */ 
    printf("\n\n"
     "1. Add file\n"
     "2. Delete file\n"
     "3. Encryption and Compression\n"
     "4. Decryption and Decompression\n"
     "5. Tutorial\n"
     "6. Exit the program\n");
}

void tutorial(void){
    char i;
    printf("Enter a section: ");
    scanf(" %c", &i);
    /*Prompts the users with a selection and uses a switch case to display
    appropirate information based on their selection*/
    switch (i){
        case '1':
            printf("Add file");
            printf("A file MUST be added to the software for it to be encrypted!");
            break;
        case '2':
            printf("DELETE FILE\n");
            printf("Allows for a chosen file to be permenantly deleted.\n NOTE: THIS ACTION IS IRREVERSIBLE!\n");
            break;
        case '3':
            printf("Encryption and Compression\n");
            printf("Allows for a chosen file to be encrypted (to prevent any unauthorized individuals to view it.\n");
            printf("The compression reduces your file size allowing for space to be maximised.\n");
            printf("WARNING: THIS ACTION IS IRREVERSIBLE! Ensure that the key is kept safe to allow for future file access.\n");
            break;
        case '4':
            printf("Decryption and Decompression\n");
            printf("Decrypts and decompresses the selected file allowing for it to be read again.\n");
            break;
        case '5':
            printf("Exit the program");
            break;
        default:
            printf("The output should be between 1 and 5");
            break;
        }
} /* prints a tutrial/decription - Connor */


int warning(void){
    char input; 
    /*ASCII Art for "WARNING" by Gene Laisne
    http://www.genelaisne.com/powershell-warnings-with-ascii-art/*/   

    printf(":::       :::     :::     :::::::::  ::::    ::: ::::::::::: ::::    :::  ::::::::\n");
    printf(":+:       :+:   :+: :+:   :+:    :+: :+:+:   :+:     :+:     :+:+:   :+: :+:    :+:\n");
    printf("+:+       +:+  +:+   +:+  +:+    +:+ :+:+:+  +:+     +:+     :+:+:+  +:+ +:+        \n");
    printf("+#+  +:+  +#+ +#++:++#++: +#++:++#:  +#+ +:+ +#+     +#+     +#+ +:+ +#+ :#:       \n");
    printf("+#+ +#+#+ +#+ +#+     +#+ +#+    +#+ +#+  +#+#+#     +#+     +#+  +#+#+# +#+   +#+# \n");
    printf(" #+#+# #+#+#  #+#     #+# #+#    #+# #+#   #+#+#     #+#     #+#   #+#+# #+#    #+# \n");
    printf("  ###   ###   ###     ### ###    ### ###    #### ########### ###    ####  ########\n\n");

    printf("This action is irreversible. Please ensure you remember your key.\n");
    printf("Press 'Y' to continue or 'C' to cancel and return to the menu: ");
    scanf(" %c", &input);
    /*Informs the user of the nature of their action and resturns their selection*/
    int output = 0; 

    while (output == 0){
      switch(input){
          case 'Y':
            output = 1;
            break;
          case 'y':
            output = 1;
            break;
          case 'C':
            output = 2;
            break;
          case 'c':
            output = 2;
            break;
          default:
            
            printf("Please ensure your input is either Y or C!:\n");
            scanf(" %c", &input);

      }

    }

    return output;
    

}

void deleteFile(){
    char filename[100]; 
    printf("Please enter a filename");
    scanf("%s", filename);
    int x = remove(filename); /* Deletes a chosen file using the remove function */
    /*remove() returns 0 if succesful*/
    if(x == 0){
        printf("File successfully deleted");
    }

    else{
        printf("ERROR: Unable to delete file.\n Please ensure the file exists and the name is correct!\n");
    }
}


