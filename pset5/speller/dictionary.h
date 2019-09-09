/**
 * Declares a dictionary's functionality.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

#define HASH_SIZE 1024 // Size of the Hash Table, arbitrary amount
#define PRIME 13 // Prime number used to multiply the hash function, helps spread the results

extern unsigned int dictSize;

// Defines the datatype: Nodes for the linked lists
typedef struct node_t
{
    char word[LENGTH + 1];
    struct node_t *next;
} node_t;

 //Initialisez the hash table: an array of nodes
node_t *hashTable[HASH_SIZE];



/**
 * Returns a numeric value, a hash function, based on the current word
 */
unsigned int hash(const char *word);

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word);

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

#endif // DICTIONARY_H
