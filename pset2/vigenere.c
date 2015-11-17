#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Not enough arguments\n");
        return 1;
    }

    string k = argv[1];
    for (int i = 0; i < strlen(k); i++)
    {
        if (!isalpha(k[i]))
        {
            printf("Only alphabetical keywords are allowed\n");
            return 1;
        }
    }

    string p = GetString();
    for (int i = 0, j = 0; i < strlen(p); i++)
    {
        if (isalpha(p[i]))
        {
            int x = isupper(p[i]) ? 65 : 97;
            int y = isupper(k[j]) ? 65 : 97;

            printf("%c", x + (p[i] - x + (k[j] - y)) % 26);
            j = (j + 1) % strlen(k);
        } else
        {
            printf("%c", p[i]);
        }
    }

    printf("\n");
}
