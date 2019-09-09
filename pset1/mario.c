#include <stdio.h>
#include <cs50.h>

//Asks user for a int, prints a half-pyramid to std output of that height

int main(void)
{
    printf("Height: ");
    int h = get_int();
    while(h > 23 || h < 0) //Checks the number is within parameters
    {
        printf("Height: ");
        h = get_int();
    }
    int blanks = h - 1;
    int hashes = 2;
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < blanks; j++)
        {
            printf(" ");
        }
        
        blanks = blanks - 1;
        
        for (int k = 0; k < hashes; k++)
        {
            printf("#");
        }
        
        hashes = hashes + 1;
        printf("\n");
    }
}