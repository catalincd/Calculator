#include <string.h>

long long getNum(char* str, int start, int end)
{
    long long sum = 0;

    for(int i=start;i<end;i++)
    {
        sum *= 10;
        sum += str[i] - '0';
    }

    return sum;
}