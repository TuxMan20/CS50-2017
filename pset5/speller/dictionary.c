/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>


#include "dictionary.h"

unsigned int dictSize = 0;

/**
 * Returns a numeric value, a hash function, based on the current word
 */
unsigned int hash(const char *word)
{

    unsigned int hashed = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        hashed = (PRIME * hashed + tolower(word[i]))  % (HASH_SIZE -1);
    }
    return hashed;

}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    int index = hash(word);

    node_t *ptr = hashTable[index];

    if (ptr == NULL) { return false; }

    do
    {
        if (strcasecmp(word, ptr->word) == 0)
        {
            return true;
        }
        else
        {
            ptr = ptr->next;
        }
    } while (ptr != NULL);

    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    int index = 0;
    FILE* dp = fopen(dictionary, "r"); // Dictionnary Pointer ... stop thinking dirty!
    if (dp == NULL)
    {
        return false;
    }
    else
    {
        char word[LENGTH + 1];


        while(fscanf(dp, "%s\n", word) != EOF)
        {
            node_t *new_node = calloc(1, sizeof(node_t)); //I changed malloc() to calloc()
            //https://stackoverflow.com/questions/30034665/initializing-an-array-of-pointers-to-null//
            if (new_node == NULL)
            {
                unload();
                return false;
            }
            else
            {
                strcpy(new_node->word, word);
                index = hash(new_node->word);
                dictSize = dictSize + 1;

                if (hashTable[index] == NULL)
                {
                    hashTable[index] = new_node;
                }
                else
                {
                    new_node->next = hashTable[index]->next;
                    hashTable[index]->next = new_node;
                }

            }


        }
        fclose(dp);
        return true;
    }
    return false;
}





/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return dictSize;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    for (int i = 0; i < HASH_SIZE; i++)
    {
        node_t *ptr = hashTable[i];

        while (ptr != NULL)
        {
            node_t *temp = ptr;
            ptr = ptr->next;
            free(temp);
        }
    }
   return true;

}
