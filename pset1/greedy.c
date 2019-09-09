#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main (void)
{
    //float quarter, dime, nickel, penny;
    int coins = 0;
    
    printf("How much change is owed?\n");
    float money = get_float();
    while(money < 0) //Checks that the amount is a positive Float
    {
        printf("How much change is owed?\n");
        money = get_float();
    }
    int cents = round(money * 100); //Converts the money to cents to avoid floats imprecisions
    
    
    while (cents >= 25) //quarters
    {
        coins++;
        cents = cents - 25;
    }
    while (cents >= 10) //dimes
    {
        coins++;
        cents = cents - 10;
    }
    while (cents >= 5) //nickels
    {
        coins++;
        cents = cents - 5;
    }
    while (cents >= 1) //pennies
    {
        coins++;
        cents = cents - 1;
    }    
    
    printf("%i\n", coins);
}