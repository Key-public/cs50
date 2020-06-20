#include <stdio.h>

int collatz(int n);

int main(void)
{
    printf("Итого %i шагов\n",collatz(5));
}

int collatz(int n)
{
    printf("%i -> ", n);
    if (n == 1)
    {
        return 0;
    }
    else if (n % 2 == 0)
    {

        return 1 + collatz(n / 2);
    }
    else
    {

        return 1 + collatz(3 * n + 1);
    }
}