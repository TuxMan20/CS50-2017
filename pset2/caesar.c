#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

//Program that takes a numeral key as input, then a phrase. It will then encrypt the word using the key.

char crypt(char usr_char, int key);

int main(int argc, string argv[])
{
    if (argc != 2 || atoi(argv[1]) < 0)
    {
        printf("Usage: Only enter one number from 1 to 25 in the command line argument\n");
        return 1;
    }
    
    int k = atoi(argv[1]);
    
    printf("plaintext: ");
    string plain = get_string();
    printf("ciphertext: ");
    
    for (int i = 0, l = strlen(plain); i < l; i++)
    {
        printf("%c", crypt(plain[i], k));
    }
    printf("\n");
}

char crypt(char usr_char, int key)
{
    
    if (isalpha(usr_char))
    {
        // Brings down the letter to a base 0-25 index for the alphabet
        // Makes all chars lowercase so we don't have to use multiple formulas
        // If the value of the char + k is over 26, the modulo brings it back 
        // within the parameters.
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