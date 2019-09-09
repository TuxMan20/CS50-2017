#include <stdio.h>
#include <cs50.h>

// convert water usage from "minutes in the shower" to the equivalent in bottles of water wasted
int main(void)
{
   printf("Minutes: ");
   int min = get_int();
   //printf("%i\n", min);
   printf("Bottles: ");
   int bottles = (min * 192)/16;
   printf("%i\n", bottles);
   
   
}