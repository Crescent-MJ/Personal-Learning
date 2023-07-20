#ifndef encryption
#define encryption

/* An enigma inspired style rotating cypher will be used
   as it is far more effective then a substitution cipher or XOR 
   cipher. 
   Outline - Encryption:
   1) A password is entered along with a key to set the starting
      position of the algorithm

   2)Each char of the .txt file passed through the algorithm 6 times and then
    saved to the encrypted version of the file.


    IMPROTANT NOTES:
     - the decryption relies on a correct password and key
        providing multiple layers for "authentication" to decrypt


   Written by - Connor
*/


/* encrypts a char string intput */ 
void encrypting(char input[], char output[], int key);
/* decrypts char string input */
void decrypting(char output[], char decrypted[], int key);
/* writes char to a txt file */
void writeFile(char input[], char *fname); 
/* reads txt file and saves into char string */
char *readFile(char *fname);
/*uses the encrypting function and file processing function to choose a file
for encryption. The encrypted text is saved to a txt file.*/
void encryptFile(char filename[]);
/* uses the decrypting function and file processing functions to choose an
encrypted file and decrypt it. The decrypted text is then saved to a txt file*/
void decryptFile(char filename[]);
/* encrypts password */
void encryptPassword(void);
/*decrypts password*/
int decryptPassword(void);

#endif
