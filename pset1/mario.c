#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int h;
    do
    {
        printf("Height: ");
        h = GetInt();
    }
    while (h > 23 || h < 0);
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < h - 1 - i; j++)
        {
            printf(" ");
        }
        for (int j = 0; j < i + 2; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
