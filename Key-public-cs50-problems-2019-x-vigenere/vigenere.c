#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int shift(char c);
char print_ciphertext(int x);
string plaintext = "plain";
string ciphertext = "cipher";
int key = 1;
int i = 1;
int counter = 0;
int main(int argc, string argv[])
   
{
    long alpha_check = 1;
    // проверка, что введено только одна строка, состоящая только из букв
    if (argc == 2)
    {
        for (int j = 0; j < strlen(argv[1]); j++)
        {
            alpha_check = alpha_check * (isalpha(argv[1][j]) / 1024);       
        }  
        if (alpha_check != 0)
        {
            plaintext = get_string("plaintext: ");
        }
        else
        {
            printf("Usage: ./caesar key\n");
            // завершаем программу, если ввод не соответствует ожидаемому
            return 1;
        }
    }
    else
    {
        printf("Usage: ./caesar key\n");
        // завершаем программу, если ввод не соответствует ожидаемому
        return 1;
    }
    printf("ciphertext: ");
    ciphertext = plaintext;
    // хитрый способ получать значения 1-26, даже если введено больше
    int length = strlen(plaintext);
    for (i = 0; i < length; i++)    
    {
        // правила шифрования для букв в нижнем регистре (должны оставаться в нижнем после подмены)
        int keyword_length = strlen(argv[1]);
        while (counter == keyword_length)
        {
            counter = 0;
        }
        key = shift(argv[1][counter]);
        // правила шифрования для букв в верхнем регистре (должны оставаться в верхнем после подмены)
        if (plaintext[i] > 64 && plaintext[i] < 91)
        {
            // хитрая логика, не позволяющая выйти за рамки диапазона
            print_ciphertext(91);
            counter++;
        }
        // правила шифрования для букв в нижнем регистре (должны оставаться в нижнем после подмены)
        else if (plaintext[i] > 96 && plaintext[i] < 123)  
        {
            print_ciphertext(123); 
            counter++;
        }
        // не буквы печатаются так же, как изначально
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

int shift(char c)
{
    if (c > 64 && c < 91) // для верхнего регистра букв
    {
        int shifting = c - 65;
        return shifting;            
    }
    else if (c > 96 && c < 123) // для нижнего регистра букв
    {
        int shifting = c - 97;
        return shifting;       
    }
    else
    {
        int shifting = 0;
        return shifting;
    }               
}
