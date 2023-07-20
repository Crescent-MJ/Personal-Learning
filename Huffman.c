#include "Huffman.h"

#include <stdio.h>/*printf(),fopen(),fclose(),fseek(),rewind(),fwrite(),
fread(),remove()*/
#include <stdlib.h>/*free(),malloc()*/
#include <string.h>/*strcpy(),strncpy(),strcat()*/

/* #define DEBUG */

HuffNode_t* create_node(char ch, int freq) {
    #ifdef DEBUG
        printf("Creating node: character='%c', frequency=%d\n", ch, freq);
    #endif
    HuffNode_t *node = (HuffNode_t*)malloc(sizeof(HuffNode_t));
    node->ch = ch;
    node->freq = freq;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void free_node(HuffNode_t *node) {
    #ifdef DEBUG
        printf("Freeing node: character='%c', frequency=%d\n", node->ch, 
        node->freq);
    #endif
    if (node != NULL) {
        free_node(node->left);
        free_node(node->right);
        free(node);
    }
}

void print_huffman_tree(HuffNode_t *root) {
    #ifdef DEBUG
        printf("Printing Huffman tree:\n");
    #endif

    if (root == NULL) {
        return;
    }
    #ifdef DEBUG
        printf("%c (%d)\n", root->ch, root->freq);
    #endif

    printf("%c (%d)\n", root->ch, root->freq);
    print_huffman_tree(root->left);
    print_huffman_tree(root->right);
}

HuffNode_t* build_huffman_tree(const char *filename) {
    int count[256] = {0}; /* Initializes the frequency count array */

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("The file can not open: %s\n", filename);
        return NULL;
    }

    int ch;
    while ((ch = fgetc(file)) != EOF) {
        count[(unsigned char)ch]++;
    }

    fclose(file);

    /* Create a leaf node and add it to the node array */
    HuffNode_t *nodes[256];
    int num_nodes = 0;
    int i;
    for (i = 0; i < 256; i++) {
        if (count[i] > 0) {
            nodes[num_nodes++] = create_node(i, count[i]);
        }
    }

    #ifdef DEBUG
        for (i = 0; i < num_nodes; i++) {
            printf("Leaf Node: char=%c, freq=%d\n", nodes[i]->character, 
            nodes[i]->freq);
        }
    #endif

    /* Build the Huffman tree */
    while (num_nodes > 1) {
        /* Find the two nodes with the least frequency */
        int min1 = 0;
        int min2 = 1;
        if (nodes[min1]->freq > nodes[min2]->freq) {
            int temp = min1;
            min1 = min2;
            min2 = temp;
        }

        for (i = 2; i < num_nodes; i++) {
            if (nodes[i]->freq < nodes[min1]->freq) {
                min2 = min1;
                min1 = i;
            } else if (nodes[i]->freq < nodes[min2]->freq) {
                min2 = i;
            }
        }

        /* Create a new node as the parent of the two smallest nodes */ 
        HuffNode_t *parent = create_node('\0', nodes[min1]->freq + 
        nodes[min2]->freq);
        parent->left = nodes[min1];
        parent->right = nodes[min2];

        /* Add the new node to the node array and remove the two nodes 
        that are already in use */
        nodes[min1] = parent;
        nodes[min2] = nodes[num_nodes - 1];
        num_nodes--;
    }

    return nodes[0]; /* Return to root node */
}

HuffNode_t* rebuild_huffman_tree(int code_length, char** codes) {
    /* Create an empty root node */
    int i,j;
    HuffNode_t* root = create_node('\0', 0);

    /* The process of building a Huffman tree */
    for (i = 0; i < code_length; i++) {
        char* code = codes[i];
        if (code == NULL) {
            continue;  /* Skip empty codes */
        }
        char ch = (char)i;  /* use index as character value */
        int freq = strlen(code);
        HuffNode_t* current = root;

        /* Traverse the encoded string and build a tree structure */
        for (j = 0; j < freq; j++) {
            if (code[j] == '0') {
                if (current->left == NULL)
                    current->left = create_node('\0', 0);
                current = current->left;
            } else if (code[j] == '1') {
                if (current->right == NULL)
                    current->right = create_node('\0', 0);
                current = current->right;
            }
        }

        #ifdef DEBUG
            printf("Node: char=%c, freq=%d\n", current->ch, current->freq);
        #endif

        /* Set the character and frequency of the current node to the 
        first character of the encoding and the length of the encoding */
        current->ch = ch;
        current->freq = freq;
    }

    return root;
}


void destroy_huffman_tree(HuffNode_t *root) {
    #ifdef DEBUG
        printf("Destroying Huffman tree:\n");
    #endif
    if (root == NULL) {
        return;
    }

    destroy_huffman_tree(root->left);
    destroy_huffman_tree(root->right);
    
    #ifdef DEBUG
        printf("Freeing node with character '%c'\n", root->ch);
    #endif
    
    free(root);
}

void generate_huffman_codes(HuffNode_t *node, const char *prefix, 
char **codes) {
    if (node == NULL) {
        return;
    }

    /* In the case of a leaf node, the encoding is saved to the corresponding
    character */
    if (node->left == NULL && node->right == NULL) {
        int index = (int)node->ch;
        codes[index] = strdup(prefix);
        
        #ifdef DEBUG
            printf("Leaf Node: char=%c, code=%s\n", node->ch, codes[index]);
        #endif

        return;
    }

    /* Recursively process the left subtree by prefixing the code with '0' */
    char *left_prefix = (char *)malloc(strlen(prefix) + 2);
    strcpy(left_prefix, prefix);
    strcat(left_prefix, "0");

    #ifdef DEBUG
        printf("Left Subtree Prefix: %s\n", left_prefix);
    #endif

    generate_huffman_codes(node->left, left_prefix, codes);
    free(left_prefix);

    /* Recursively process the right subtree by prefixing the code with '1' */
    char *right_prefix = (char *)malloc(strlen(prefix) + 2);
    strcpy(right_prefix, prefix);
    strcat(right_prefix, "1");

    #ifdef DEBUG
        printf("Right Subtree Prefix: %s\n", right_prefix);
    #endif

    generate_huffman_codes(node->right, right_prefix, codes);
    free(right_prefix);
}

CompressionResult_t compress_data(const char* filename, 
char** codes, int* compressed_size) {
    CompressionResult_t result;
    result.compressed_data = NULL;
    result.compressed_size = 0;
    result.codes = NULL;

    FILE* input_file = fopen(filename, "rb");
    if (input_file == NULL) {
        printf("Unable to open file: %s\n", filename);
        return result;
    }

    fseek(input_file, 0, SEEK_END);
    long input_size = ftell(input_file);
    rewind(input_file);

    unsigned char* compressed_data = (unsigned char*)malloc((input_size + 1)
    * sizeof(unsigned char));
    if (compressed_data == NULL) {
        printf("Memory allocation failure\n");
        fclose(input_file);
        return result;
    }

    int index = 0;
    unsigned char buffer = 0;
    int bit_count = 0;

    int ch;
    int i;
    while ((ch = fgetc(input_file)) != EOF) {
        char* code = codes[ch];

        for (i = 0; code[i] != '\0'; i++) {
            buffer = buffer << 1;
            if (code[i] == '1') {
                buffer = buffer | 1;
            }
            bit_count++;

            if (bit_count == 8) {
                if (index >= input_size) {
                    /* Extend compressed data buffer */
                    compressed_data = realloc(compressed_data, 
                    (index + input_size) * sizeof(unsigned char));
                    if (compressed_data == NULL) {
                        printf("Memory allocation failure\n");
                        fclose(input_file);
                        free(compressed_data);
                        return result;
                    }
                }
                compressed_data[index++] = buffer;
                buffer = 0;
                bit_count = 0;
            }
        }
    }

    if (bit_count > 0) {
        if (index >= input_size) {
            /* Extend compressed data buffer */
            compressed_data = realloc(compressed_data, 
            (index + input_size + 1) * sizeof(unsigned char));
            if (compressed_data == NULL) {
                printf("Memory allocation failure\n");
                fclose(input_file);
                free(compressed_data);
                return result;
            }
        }
        buffer = buffer << (8 - bit_count);
        compressed_data[index++] = buffer;
    }

    compressed_data[index] = '\0';

    fclose(input_file);

    result.compressed_data = compressed_data;
    result.compressed_size = index;
    result.codes = NULL;

    *compressed_size = index;

    #ifdef DEBUG
        printf("Compressed Data: %s\n", compressed_data);
        printf("Compressed Size: %d\n", *compressed_size);
    #endif

    return result;
}

void compress_file(const char* input_filename, const char* output_filename) {
    /* open input file */
    int i;
    FILE* input_file = fopen(input_filename, "rb");
    if (input_file == NULL) {
        printf("Unable to open file:%s\n", input_filename);
        return;
    }

    /* Create output file */
    FILE* output_file = fopen(output_filename, "wb");
    if (output_file == NULL) {
        printf("Unable to create file: %s\n", output_filename);
        fclose(input_file);
        return;
    }

    /* Build a Huffman tree */
    HuffNode_t* root = build_huffman_tree(input_filename);

    /* Create a Huffman encoding table */
    char* codes[256] = { NULL };

    /* Generate Huffman codes */
    generate_huffman_codes(root, "", codes);

    /* Write Huffman code length */
    int code_length = 0;
    for (i = 0; i < 256; i++) {
        if (codes[i] != NULL) {
            code_length++;
        }
    }
    fwrite(&code_length, sizeof(int), 1, output_file);

    /* Write Huffman codes and characters */
    for (i = 0; i < 256; i++) {
        if (codes[i] != NULL) {
            int code_size = strlen(codes[i]);
            fwrite(&code_size, sizeof(int), 1, output_file);
            fwrite(codes[i], sizeof(char), code_size, output_file);
            fputc((char)i, output_file);
        }
    }

    #ifdef DEBUG
        for (i = 0; i < 256; i++) {
            if (codes[i] != NULL) {
                printf("Character: %c, Code: %s\n", (char)i, codes[i]);
            }
        }
    #endif

    /* Compress data and write to output file */
    int compressed_size = 0;
    CompressionResult_t compression_result = compress_data(input_filename, codes, &compressed_size);
    fwrite(compression_result.compressed_data, sizeof(unsigned char), compressed_size, output_file);

    /* free memory */
    for (i = 0; i < 256; i++) {
        if (codes[i] != NULL) {
            free(codes[i]);
        }
    }
    free(compression_result.compressed_data);
    destroy_huffman_tree(root);

    /* Close the file */
    fclose(input_file);
    fclose(output_file);
    printf("End of the compression\n");
}

void decompress_data(const char* filename, const unsigned char* compressed_data, int compressed_size, HuffNode_t* root) {
    /* Create output file */ 
    FILE* output_file = fopen(filename, "w");
    if (output_file == NULL) {
        printf("Unable to create file: %s\n", filename);
        return;
    }

    if (root == NULL) {
        printf("Error: Invalid Huffman tree. Root node is NULL.\n");
        fclose(output_file);
        return;
    }

    if (compressed_data == NULL || compressed_size == 0) {
        printf("No data to decompress.\n");
        fclose(output_file);
        return;
    }

    HuffNode_t* current_node = root;
    int i, j;
    for (i = 0; i < compressed_size; i++) {
        unsigned char byte = compressed_data[i];
        for (j = 7; j >= 0; j--) {
            unsigned char bit = (byte >> j) & 1;

            #ifdef DEBUG
                        /* Debug: Print current bit */
                        printf("Bit: %d\n", bit);
            #endif

            if (current_node == NULL) {
                printf("Error: Invalid Huffman tree. Current node is NULL.\n");
                fclose(output_file);
                return;
            }

            if (bit == 0) {
                current_node = current_node->left;
            } else {
                current_node = current_node->right;
            }

            if (current_node != NULL && current_node->left == NULL && current_node->right == NULL) {
                fprintf(output_file, "%c", current_node->ch);
                current_node = root;
            }
        }
    }

    /* close file */
    fclose(output_file);
}

void decompress_file(const char* input_filename, const char* output_filename) {
    /* read compressed file */ 
    char* codes[256] = { NULL }; /* initialized to a NULL pointer*/ 
    FILE* input_file = fopen(input_filename, "rb");
    if (input_file == NULL) {
        printf("Unable to open input file: %s\n", input_filename);
        return;
    }

    /* Create output file */ 
    FILE* output_file = fopen(output_filename, "w");
    if (output_file == NULL) {
        printf("Unable to create file: %s\n", output_filename);
        fclose(input_file);
        return;
    }

    /* Read Huffman code length */ 
    int code_length;
    fread(&code_length, sizeof(int), 1, input_file);

    /* Read Huffman codes and characters */
    int i;
    for (i = 0; i < code_length; i++) {
        int code_size;
        fread(&code_size, sizeof(int), 1, input_file);
        char* code = (char*)malloc((code_size + 1) * sizeof(char));
        if (code == NULL) {
            printf("Memory allocation failed for code[%d]\n", i);
            fclose(input_file);
            fclose(output_file);
            return;
        }
        fread(code, sizeof(char), code_size, input_file);
        code[code_size] = '\0';
        unsigned char ch;
        fread(&ch, sizeof(unsigned char), 1, input_file);
        codes[ch] = code;
    }

    /* Get the starting position of the compressed data */ 
    long compressed_data_start = ftell(input_file);

    /* Jump to end of compressed data */ 
    fseek(input_file, 0, SEEK_END);
    long compressed_data_end = ftell(input_file);

    /* Calculate the size of the compressed data */ 
    long compressed_size = compressed_data_end - compressed_data_start;

    /* Move the file pointer to the beginning of the compressed data */ 
    fseek(input_file, compressed_data_start, SEEK_SET);

    /* read compressed data */ 
    unsigned char* compressed_data = (unsigned char*)malloc(compressed_size 
    * sizeof(unsigned char));
    if (compressed_data == NULL) {
        printf("Memory allocation failed for compressed_data\n");
        fclose(input_file);
        fclose(output_file);
        return;
    }
    fread(compressed_data, sizeof(unsigned char), compressed_size, input_file);

    /* close input file */ 
    fclose(input_file);

    /* Rebuild the Huffman tree */ 
    int num_symbols = 256; /* Need to traverse the list */ 
    HuffNode_t* root = rebuild_huffman_tree(num_symbols, codes);
    if (root == NULL) {
        printf("Failed to rebuild Huffman tree\n");
        fclose(output_file);
        return;
    }

    #ifdef DEBUG
        printf("Starting decompression...\n");
    #endif
    /* decompress data */ 
    decompress_data(output_filename, compressed_data, compressed_size, root);

    #ifdef DEBUG
        printf("Decompression complete.\n");
    #endif

    /* free memory */ 
    for (i = 0; i < 256; i++) {
        if (codes[i] != NULL) {
            free(codes[i]);
        }
    }
    free(compressed_data);
    destroy_huffman_tree(root);

    printf("End of the decompression\n");

    fclose(output_file);
}

void compression_decompression(const char* input_filename, int i) {

    char compressed_filename[100];
    char output_filename[100];

    #ifdef DEBUG
        printf("input_filename: %s\n", input_filename);
        printf("i: %d\n", i);
    #endif

    if (i == 0) {
        printf("Starting Compression ...... \n");

        #ifdef DEBUG
                printf("Performing compression...\n");
        #endif

        /* Generate compressed filename */
        FILE* file = fopen(input_filename, "r");
        if (file != NULL) {
            #ifdef DEBUG
                printf("The file is working.\n");
            #endif
            fclose(file);
        } else {
            printf("The file cannot open.\n");
            return;
        }

        strncpy(compressed_filename, input_filename, sizeof(compressed_filename) - 1);
        compressed_filename[sizeof(compressed_filename) - 1] = '\0';

        char* compression = strrchr(compressed_filename, '.');
        if (compression != NULL) {
            strcpy(compression, ".bin");
        } else {
            strcat(compressed_filename, ".bin");
        }

        /* Compressed file */
        compress_file(input_filename, compressed_filename);
        printf("File compressed successfully.\n");
        delete_file(input_filename);

    } else if (i == 1) {
        printf("Starting Decompression ...... \n");

        #ifdef DEBUG
            printf("Performing decompression...\n");
        #endif

        /* generate decompressed filename */
        FILE* file = fopen(input_filename, "r");
        if (file != NULL) {
            #ifdef DEBUG
                printf("The file is working.\n");
            #endif
            fclose(file);
        } else {
            printf("The file cannot open.\n");
            return;
        }
        strncpy(output_filename, input_filename, sizeof(output_filename) - 1);
        output_filename[sizeof(output_filename) - 1] = '\0';

        char* decompression = strrchr(output_filename, '.');
        if (decompression != NULL) {
            strcpy(decompression, ".txt");
        } else {
            strcat(output_filename, ".txt");
        }

        /* decompress the file */
        decompress_file(input_filename, output_filename);
        printf("File decompressed successfully.\n");
        delete_file(input_filename);

    }
    return;
}

void delete_file(const char* filename) {
    #ifdef DEBUG
        printf("Deleting file: %s\n", filename);
    #endif
    if (remove(filename) == 0) {
        printf("File '%s' deleted successfully.\n", filename);
    } else {
        printf("Failed to delete file '%s'.\n", filename);
    }
}

