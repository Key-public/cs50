"""
Код, написанный на Си, для переделки в Py
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    for (int i = 1; i <= height; i++)
    {
        for (int j = height - i; j > 0; j--)
        {
            printf(" ");
        }
        for (int k = 1; k <= i; k++)
        {
            printf("#");
        }
        printf("  ");
        for (int m = 1; m <= i; m++)
        {
            printf("#");
        }
        printf("\n");
    }
}
"""

from cs50 import get_int
# Проверяем ввод
while True:
    height = get_int("Height: ")
    if height > 0 and height < 9:
        break
# Строим пирамиду (можно обойтись вообще без циклов О_О)
for i in range(height):
    print(" " * (height - i - 1), end="")
    print("#" * (i + 1), end="")
    print("  ", end="")
    print("#" * (i + 1), end="")
    print("")
