#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char print_ciphertext(int x);
string plaintext = "plain";
string ciphertext = "cipher";
int key = 1;
int i = 1;
int main(int argc, string argv[])
   
{
    long digits_check = 1;
    // проверка, что введены только цифры (любое умножение на 0 сделает переменную digits_check равной нулю)
    
    // проверка, что введено только одно число (и ничего больше)
    if (argc == 2)
    {
        for (int j = 0; j < strlen(argv[1]); j++)
        {
            digits_check = digits_check * (isdigit(argv[1][j]) / 2048);       
        }  
        if (digits_check != 0)
        {
            plaintext = get_string("plaintext: ");
        }
        else
        {
            printf("Usage: ./caesar key1\n");
            // завершаем программу, если ввод не соответствует ожидаемому
            return 1;
        }
    }
    else
    {
        printf("Usage: ./caesar key1\n");
        // завершаем программу, если ввод не соответствует ожидаемому
        return 1;
    }
    printf("ciphertext: ");
    ciphertext = plaintext;
    // хитрый способ получать значения 1-26, даже если введено больше
    key = (26 + atoi(argv[1])) % 26;
    int length = strlen(plaintext);
    for (i = 0; i < length; i++)    
    {
        // правила шифрования для букв в нижнем регистре (должны оставаться в нижнем после подмены)
        if (plaintext[i] > 64 && plaintext[i] < 91)
        {
            // хитрая логика, не позволяющая выйти за рамки диапазона
            print_ciphertext(91);
        }
        // правила шифрования для букв в верхнеи регистре (должны оставаться в верхнем после подмены)
        else if (plaintext[i] > 96 && plaintext[i] < 123)  
        {
            print_ciphertext(123);          
        }
        // всё, что не буквы печатается так же, как изначально
        else
        {
            printf("%c", plaintext[i]); 
        }   
    }   
    printf("\n");
    return 0;
}

char print_ciphertext(int x)
// хитрая логика, не позволяющая выйти за рамки диапазона
{
    if ((int) plaintext[i] + key >= x) // х == 91 или 123
    {
        ciphertext[i] = plaintext[i] - 26 + key;
        printf("%c", ciphertext[i]);
        return ciphertext[i];
    }
    else
    {
        ciphertext[i] = plaintext[i] + key;
        printf("%c", ciphertext[i]);
        return ciphertext[i];
    }
}
