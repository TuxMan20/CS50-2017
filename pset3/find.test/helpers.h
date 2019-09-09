/**
 * helpers.h
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n);
    // Your implementation must return false immediately if n is non-positive.
    // Your implementation must return true if value is in values and false if value is not in values.
    // The running time of your implementation must be in O(log n).
    // You may not alter the function’s declaration.
    

/**
 * Sorts array of n values.
*/
void sort(int values[], int n);
