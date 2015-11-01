#include <cs50.h>
#include <math.h>
#include <stdio.h>

float COINS[4] = {0.25, 0.1, 0.05, 0.01};

int change(float in, int coinIndex)
{
    int i = (int)(in / COINS[coinIndex]);
    float f = roundf(fmod(in, COINS[coinIndex]) * 100) / 100;

    if (f == 0.00)
    {
        return i;
    }

    return i + change(f, coinIndex + 1);
}

int main(void)
{
    float f = -1;
    printf("O hai!");

    while (f < 0)
    {
        printf("How much change is owed?\n");
        f = GetFloat();
    }

    printf("%i\n", change(f, 0));
}
