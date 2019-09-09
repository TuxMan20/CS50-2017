/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>
#include <string.h>
#include <stdlib.h>

#include "helpers.h"

static int compare (void const *a, void const *b)
{
   /* definir des pointeurs type's et initialise's
      avec les parametres */
   int const *pa = a;
   int const *pb = b;

   /* evaluer et retourner l'etat de l'evaluation (tri croissant) */
   return *pa - *pb;
}


/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
   //// Easy Quick Sort already implemented in stdlib////

    //qsort(values, n, sizeof(int), compare);

    /////Implementation of a counting sort

    int maxValue, pos = 0; // Will store the highest number in the array, and the position to bring back the sorted values

    for (int i = 0; i < n; i++) // Finds the highest value
    {
        if (maxValue < values[i]) // If the current value in the array is higher than maxValue, it becomes maxValue
        {
            maxValue = values[i];
        }
    }

    int count[maxValue]; // will store the count values, as many position as the highest value in the array
    memset(count, 0, sizeof count); // Fills every positions with 0, very important because these will be used to count

    for (int i = 0; i <= n; i++)
    {
        count[values[i]]++; // Checks the value in the unsorted list, adds 1 to the position of that value in the count array
    }                       // Eg: value 234 in the list, count[234] ++
    for (int i = 0; i < maxValue; i++)
    {
        while (count[i] > 0) // Goes over the count array, replaces the values in the unsorted list with values equal to
        {                    // the position of the counting array where its value is higher than 0
            values[pos] = i;
            pos = pos + 1; // Makes sure the next sorted entry will be next in the array
            count[i] = count[i] - 1; // If the count was 3, 2, 1... makes sure it will be recounted or brought to 0
        }

    }


    return;
}
