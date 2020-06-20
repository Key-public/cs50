from cs50 import get_string
from sys import argv, exit


def main():
    # проверка, что введено только одно число (и ничего больше)
    if len(argv) == 2 and argv[1].isdigit() and int(argv[1]) >= 0:
        plaintext = get_string("plaintext: ")
    else:
        print("Usage: python caesar.py key")
        exit(1)

    # сохраняем ключ, предварительно поделив его по модулю на 26 (чтобы учесть ввод > 26)
    key = int(argv[1]) % 26

    # заголовок для будущего вывода
    print("ciphertext: ", end="")

    # начинаем шифровку
    for c in plaintext:
        if ord(c) > 64 and ord(c) < 91:
            print_ciphertext(91, c, key)
        elif ord(c) > 96 and ord(c) < 123:
            print_ciphertext(123, c, key)
        else:
            print(c, end="")
    print()
    exit(0)


def print_ciphertext(x, c, key):
    if (ord(c) + key) >= x:
        print(chr(ord(c) - 26 + key), end="")
    else:
        print(chr(ord(c) + key), end="")


main()
