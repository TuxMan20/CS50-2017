/*
    Test Program to experiement methods of determining the size of an array
*/

#include <stdio.h>
#include <cs50.h>

int main (void)
{
    int array[] = {1,2,3,4,5,6,7,8};
    int bySizeof;
    
    /*for (int i = 0; check != NULL; i++)
    {
        byLoop = byLoop + 1;
        check = array[i];
    }*/
    
    bySizeof = sizeof(array)/sizeof(array[0]);
    
    printf("The size of the Array is:\nSizeof: %i\n", bySizeof);
}