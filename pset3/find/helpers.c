/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // Set values for the top and the bottom of the search
    int lower = 0;
    int upper = n - 1;

    // binary search
    while (lower <= upper)
    {
        // find the middle
        int middle = (upper + lower) / 2;

        // compare middle to wanted value
        if (values[middle] == value)
        {
            // job's done
            return true;
        }
        else if (values[middle] < value)
        {
            // take the right part
            lower = middle + 1;
        }
        else if (values[middle] > value)
        {
            // take the left part
            upper = middle - 1;
        }
    }

    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // for loop inside the array
    for (int j = 0; j < n ; j++)
    {
        // iniate swap counter
        int swaps = 0;

        /*
        * Swap adjacent elements if out of order
        *
        * iterate through the array
        */

        for (int i = 0; i < n - 1; i++)
        {
            // check is values[i] > values[i+1]. If so, swap them
            if (values[i] > values[i + 1])
            {
                int tmp = values[i + 1];
                values[i + 1] = values[i];
                values[i] = tmp;
                swaps++;
            }
        }

        // if not swap, leave the loop
        if (!swaps)
        {
            break;
        }
    }
}
