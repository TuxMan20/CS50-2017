/************
vigenere.c
Purpose:    Takes in an encryption key composed of a word 
            as a command line argument(string k;).
            The user then enters a phrase where each letters will be shifted
            by "x" positions based on the letters of the key. Each letters of the 
            key will represent a numeric value (a = 0, b = 1, etc...)
             
by Louis-Philippe Morier, for CS50x 2017
************/

#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

// Program that takes a alpha key as input, converts it to a rolling 
// numeric key, then a phrase. It will then encrypt the word using the key.


char crypt(char usr_char, int key);

int main(int argc, string argv[])
{
    
    // Sanity checks for the command line arguments
    if (argc != 2) //Checks if the user entered a key
    {
        printf("Usage: Enter a word as a cryptographic key in the command line argument (Error 1)\n");
        return 1;
    }
    
    int l = strlen(argv[1]); // Length of the key
    
    for(int i = 0; i < l; i++) // Verifies the user entered only letters as the key
    {
        if(!isalpha(argv[1][i]))
        {
            printf("Usage: Use only letters as a key. No numbers, punctuations or symbols permitted. (Error 1)\n");
            return 1;
        }
    }
    
    int p = 0; // Keeps tracks of the position inside the key word
    int k = 0; // Will be used as the key value
    
    printf("plaintext: ");
    string plain = get_string();
    printf("ciphertext: ");
    
    for (int i = 0, m = strlen(plain); i < m; i++)
    {
        k = tolower(argv[1][p]) - 97;
        printf("%c", crypt(plain[i], k));
        
        if(isalpha(plain[i]) != 0) // Only shift key position if the current char is a letter
        {
            p = (p + 1) % l; // Move along and wrap around the key word
        }
        
    }
    printf("\n");
}

char crypt(char usr_char, int key)
{
    
    if (isalpha(usr_char))
    {
        // Brings down the ASCII letter to a base 0-25 index for the alphabet
        // Makes all chars lowercase so we don't have to use multiple formulas
        // If the value of the char + k is over 26, the modulo brings it back 
        // within the parameters (Eg: Z rolls over to A). 
        char crypted = (((tolower(usr_char)-97) + key) % 26) + 97;
        
        // If the char was uppercase in the first place, makes it
        // upper case again before being returned.
        if (isupper(usr_char))
        {
            crypted = toupper(crypted);
        }
        return crypted;
    }
    else return usr_char; //Any other char, simply return it as is.
}