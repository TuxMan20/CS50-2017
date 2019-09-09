#include <stdio.h>
#include <cs50.h>

//Program that checks if a credit card number is valid, and returns the issuing company of the card

int main (void)
{
    long long number = 378282246310005;
    
    char card_array[sizeof(number)] = [0];
    
    /*for(int i = 0; i < sizeof(number); i++)
    {
        
    }*/
    
    printf("%c", card_array[0]);
}