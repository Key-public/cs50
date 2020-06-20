from cs50 import get_string
from sys import argv


def main():
    # провекрка, что аргумента только 2
    if len(argv) != 2:
        print("Usage: python bleep.py dictionary")
        exit(1)
    # попытка открыть файл и записать его содержимое в массив построчно и с обрезкой переноса строки
    try:
        fo = open(argv[1], "r")
    except:
        print("No such file")
        exit(2)
    dictionary = fo.readlines()
    for i in range(len(dictionary)):
        dictionary[i] = dictionary[i].strip("\n")
    # если всё получилось, запрашиваем текст на проверку
    text = get_string("What message would you like to censor?\n")
    # делим предложение по словам
    words = text.split()
    # работаем с каждым отдельным словом, преводя всё к нижнему регистру и высекая лишние символы
    k = 0
    for k in range(len(words)):
        word_in_lower = words[k].lower()
        # а теперь работаем с буквами, превращая их в звёздочки
        if (word_in_lower in dictionary):
            i = 0
            for i in range(len(words[k])):
                words[k] = words[k].replace(words[k][i], "*")
                i += 1

    print(" ".join(words))
    fo.close()
    exit(0)


if __name__ == "__main__":
    main()
