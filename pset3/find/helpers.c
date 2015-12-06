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

bool binarysearch(int values[], int value, int lo, int hi)
{
    if (lo > hi) return false;

    int p = (lo + hi) / 2;
    if (values[p] > value) return binarysearch(values, value, lo, p - 1);
    if (values[p] < value) return binarysearch(values, value, p + 1, hi);
    return true;
}

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    return binarysearch(values, value, 0, n);
}

// Pointer operations ftw
void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void quicksort(int values[], int lo, int hi)
{
    if (lo > hi) return;

    int pivot = values[hi];
    int p = lo;

    for (int i = lo; i < hi; i++)
    {
        if (values[i] <= pivot)
        {
            swap(&values[p], &values[i]);
            p = p + 1;
        }
    }

    swap(&values[p], &values[hi]);
    quicksort(values, lo, p - 1);
    quicksort(values, p + 1, hi);
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    quicksort(values, 0, n);
}
