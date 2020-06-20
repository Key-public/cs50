#include <stdio.h>

void switch_k(int k);
void switch_pk(int* pk);

int main (void)
{
    int k = 2;
    int* pk = &k;
    printf("Значение \"%i\" находится в памяти по адресу \"%i\" \n", k, *pk);
    switch_k(k);
    printf("После switch_k значение \"%i\" находится в памяти по адресу \"%i\" \n", k, *pk);
    switch_pk(pk);
    printf("После switch_pk значение \"%i\" находится в памяти по адресу \"%i\" \n", k, *pk);
}

void switch_k(int k)
{
    k = k + 1;
}

void switch_pk(int* pk)
{
    *pk = *pk + 1;
}