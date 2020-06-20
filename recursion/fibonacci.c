#include <stdio.h>

int fibonacсi(int n);

int main(void)
{
    int n;
    printf("Сколько чисел вывести?\n");
    scanf("%d", &n);
    for (int k = 1; k <= n; k++)
    {
        printf("%i ", fibonacсi(k));
    }
    printf("\n");
}

int fibonacсi(int n)
{
        if (n == 1 || n == 2)
        {
            return 1;
        }
        return fibonacсi(n - 1) + fibonacсi(n - 2);
}