/*
Huffman code Outline:

    1. Character Frequency Counting:
Read the data to be compressed and count the frequency of each character.

    2. Construct a Huffman Tree: 
Construct a Huffman tree based on the character frequency.

    3. Generate Huffman Codes: 
Traverse the Huffman tree to generate the Huffman code for each character 
and store the encoding table.

    4. Compress data: 
Use the generated encoding table to compress the original data and store 
the compressed data in a file.

    5. Decompress data: 
Read the encoding table the compressed data from the compressed file, 
decode the compressed data according to the encoding table,and get the 
original data.
    -- written by Mengjing --
*/

#ifndef Huffman
#define Huffman

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* The node of the huffman tree */
struct huff_node{
    char ch;
    int freq;
    struct huff_node *left, *right;
};
typedef struct huff_node HuffNode_t;

struct CompressionResult{
    unsigned char* compressed_data;
    int compressed_size;
    char** codes;
    const char* error;
};
typedef struct CompressionResult CompressionResult_t;

/* Create a Huffman tree node */ 
HuffNode_t* create_node(char ch, int freq);
/* Free the Huffman tree node */ 
void free_node(HuffNode_t *node);
/* Show Huffman tree */
void print_huffman_tree(HuffNode_t *root);
/* Create a Huffman tree */ 
HuffNode_t* build_huffman_tree(const char *filename);
/* Destroy the Huffman tree */ 
void destroy_huffman_tree(HuffNode_t *root);
/* Generate Huffman codes */ 
void generate_huffman_codes(HuffNode_t *root, const char *prefix, char **codes);
/* Rebuild Huffman Tree according to Huffman Code */
HuffNode_t* rebuild_huffman_tree(int code_length, char** codes);
/* delete source file */
void delete_file(const char* filename);
/* Compressed data */
CompressionResult_t compress_data(const char* filename, char** codes, 
int* compressed_size);
/* Decompressed data */ 
void decompress_data(const char* filename, 
const unsigned char* compressed_data, int compressed_size, HuffNode_t* root);
/* Compressed file */
void compress_file(const char* input_filename, const char* output_filename);
/* Decompressed file */
void decompress_file(const char* input_filename, const char* output_filename);
/* Call the compression or decompression program */
void compression_decompression (const char* input_filename, int i);

#endif
