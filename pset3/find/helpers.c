/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
        
#include <cs50.h>
 
#include "helpers.h"
 
/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a BINARY searching algorithm
    int begin = 0;
    int end = n-1;
    int mid;
     
    while(end >= begin) // Loop ensures the entire array is searched until one position is left
    {
        mid = (begin + end) / 2; // FInds the middle of the array, or of what is left to search
         
        if(values[mid] == value)
        {
            return true;
        }
        else if(values[mid] > value)
        {
            end = mid - 1;
        }
        else
        {
            begin = mid + 1;
        }
    }
    return false;
 
}
 
/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    /* swap is a marker: as long as it is flagged as true, it means there has been 
       two positions that swapped in the last pass. There will be another pass as long as
       nothing swaps. Then the loop ends.
       Bubble Sort used below.
    */
    bool swap = true;
    while (swap)
    {
        swap = false;
        int temp;
        for (int i = 0; i < n-1; i++)
        {
            if (values[i] > values[i + 1])
            {
                temp = values[i + 1];
                values[i + 1] = values[i];
                values[i] = temp;
                swap = true;
            }
        }
    }
    return;
}