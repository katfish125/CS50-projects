/*
* This program encrypts a message using the vigenere method.
*/

#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // checks if input format is acceptable
    if (argc != 2)
    {
        printf("Please try again :( \n");
        return 1;
    }
    
    // gets key and prompts for input
    string k = argv[1];
    int klen = strlen(k);
    
    // turns string key to int
    for (int i = 0; i < klen; i++)
    {
        if (isalpha(k[i]) == false)
        {
            printf("Please try again :( \n");
            return 1;
        }
        int num = k[i];
        if (islower(k[i]))
        {
            num = k[i] - 'a';
        }
        else
        {
            num = k[i] - 'A';
        }
        k[i] = num;
    }
    
    // prompts user for input and encrypts
    string string = GetString();
    int slen = strlen(string);
    // scount is string letter count
    int scount = 0;
    for (int i = 0; i < slen; i++)
    {
        if (isalpha(string[i]))
        {
            // kcount is char count for k
            int kcount = scount % klen;
            int klet = k[kcount];
            int curlet = string[i];
            if (islower(curlet))
            {
                curlet = ( curlet - 'a' + klet ) % 26 + 'a';
            }
            else
            {
                curlet = ( curlet - 'A' + klet ) % 26 + 'A';
            }
            string[i] = curlet;
            scount = scount + 1;
        }
        printf("%c", string[i]);
    }
    printf("\n");
}
