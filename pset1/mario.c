#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h = -1;

    while (h < 0 || h > 23)
    {
        printf("height: ");
        h = GetInt();
    }

    for (int i = h; i > 0; i--)
    {
        for (int j = i - 1; j > 0; j--)
        {
            printf(" ");
        }

        for (int j = h - i + 1; j > 0; j--)
        {
            printf("#");
        }

        printf("#\n");
    }
}
