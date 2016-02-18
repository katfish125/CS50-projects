/*
* This is a program for encrypting messages using the caesar method.
*/

#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    // checks if key format is acceptable
    if (argc != 2)
    {
        printf("Format not accepted, please try again.\n");
        return 1;
    }
    
    // gets key and input
    int k = atoi(argv[1]);
    string p = GetString();
    
    // prints out encrypted chars one by one
    for (int i = 0, n = strlen(p); i < n; i++)
    {
        // checks for lower/uppercase letters
        if (islower(p[i]))
        {
            p[i] = (p[i] - 'a' + k % 26) % 26 + 'a';
        }
        else if (isupper(p[i]))
        {
            p[i] = (p[i] - 'A' + k % 26) % 26 + 'A';
        }
        printf("%c", p[i]);
    }
    printf("\n");
}
