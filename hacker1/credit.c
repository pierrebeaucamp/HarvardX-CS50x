#include <cs50.h>
#include <stdio.h>

bool check(long l)
{
    static char buf[16];
    snprintf(buf, 17, "%li", l);

    int sum = 0;
    for (int i = 15; i >= 0; i--)
    {
        int tmp = buf[i] - '0';

        // happens with short CC numbers
        if (tmp < 0)
        {
            break;
        }

        if ((15 - i) % 2 == 0)
        {
            sum += tmp;
            continue;
        }

        tmp *= 2;
        static char tmpBuf[2];
        snprintf(tmpBuf, 3, "%i", tmp);

        sum += tmpBuf[0] - '0';
        if (tmp >= 10)
        {
            sum += tmpBuf[1] - '0';
        }
    }

    if (sum % 10 == 0)
    {
        return true;
    }

    return false;
}

char * type(long l)
{
    static char buf[1];
    snprintf(buf, 2, "%li", l);

    switch (buf[0] - '0')
    {
        case 3:
            return "AMEX";

        case 4:
            return "VISA";

        case 5:
            return "MASTERCARD";
    }

    return "INVALID";
}

int main(void)
{
    printf("Number: ");
    long l = GetLongLong();

    if (check(l))
    {
        printf("%s\n", type(l));
        return 0;
    }

    printf("INVALID\n");
}
