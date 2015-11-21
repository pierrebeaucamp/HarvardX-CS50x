#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// crack():
// char* input: the encrypted string
// int length:  the length of the key
// char* salt:  the salt of the encryption
// char* buf:   the output buffer
// int pos:     the current index of our key
//
// returns char* if a key was found, otherwise NULL
char* crack(char* input, int length, char* salt, char* key, int pos)
{
    // Iterating over all printable ASCII characters
    for (int c = 32; c <= 126; c++)
    {
        key[pos] = c;

        // Populate the remaining chars of the key
        if (pos + 1 < length)
        {
            char* tmp = crack(input, length, salt, key, pos + 1);
            if (tmp != NULL)
                return tmp;
            free(tmp);
        }

        // If we found a match, return it
        if (strncmp(input, crypt(key, salt), 13) == 0)
            return key;
    }

    return NULL;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Not enough arguments\n");
        return 1;
    }

    // Get the salt
    char salt[3];
    strncpy(salt, argv[1], 2);
    salt[2] = '\0';

    // In this exercise, a key has no more than eight characters.
    int keySize = 8;
    char buf[keySize];
    for (int length = 1; length <= keySize; length++)
    {
        char* key = crack(argv[1], length, salt, buf, 0);
        if (key != NULL)
        {
            printf("%s\n", key);
            return 0;
        }
    }

    printf("No solution found.");
}

