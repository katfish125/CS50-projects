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

bool binary_search(int A[], int key, int imin, int imax);

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    if(n < 0)
        return false;
    if(binary_search(values, value, 0, n -1))
        return true;
    else
        return false;
}

//binary search function called by the search function
bool binary_search(int A[], int key, int imin, int imax)
{
  if (imax < imin)
    return false;
  else
    {
      int imid = (imin + imax) / 2;
 
      if (A[imid] > key)
        // NOTE: the return below is the key to successful searching!!
        return binary_search(A, key, imin, imid-1);
      else if (A[imid] < key)
        return binary_search(A, key, imid+1, imax);
      else
        return true;
    }
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    int tmp;
    int min;
    int index;
    for (int i = 0; i < n; i++)
    {
        min = values[i];
        index = 0;
        for (int j = i + 1; j < n; j++)
        {
            if(values[j] < min)
            {
                min = values[j];
                index = j;
            }
        }
        if (index != 0)
        {
            tmp = values[i];
            values[i] = values[index];
            values[index] = tmp;
        }
        printf("%d\n", values[i]);
    }
}
