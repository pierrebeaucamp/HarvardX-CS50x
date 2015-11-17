#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Not enough arguments\n");
        return 1;
    }

    int k = atoi(argv[1]);
    string p = GetString();

    for (int i = 0; i < strlen(p); i++)
    {
        if (isalnum(p[i]) && !isdigit(p[i]))
        {
            int x = isupper(p[i]) ? 65 : 97;
            printf("%c", x + (p[i] - x + k) % 26);
        } else
        {
            printf("%c", p[i]);
        }
    }

    printf("\n");
}
