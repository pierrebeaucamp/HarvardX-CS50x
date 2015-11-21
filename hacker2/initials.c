#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string s = GetString();

    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] != ' ' && (i == 0 || s[i - 1] == ' '))
        {
            printf("%c", toupper(s[i]));
        }
    }

    printf("\n");
}
