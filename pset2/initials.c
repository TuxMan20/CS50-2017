#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//Program that asks user for a name then give out the initials

int main(void)
{
    bool space = true; 
    string name = get_string();
    int l = strlen(name);
    
    for(int i = 0; i < l; i++)
    {
        if (name[i] >= 65 && name[i] <= 90 && space == true) //Checks for upper case first letters
        {
            space = false;
            printf("%c", name[i]);
        }
        if (name[i] >= 97 && name[i] <= 122 && space == true) //Checks for lower case first letters
        {
            space = false;
            printf("%c", toupper(name[i]));
        }
        
        if (name[i] == ' ') //Checks if the character is a space, which means the next letter is an initial
        {
            space = true;
        }
        else space = false;
    }
    printf("\n");
}