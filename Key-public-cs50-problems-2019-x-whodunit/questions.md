# Questions

## What's `stdint.h`?

Файл, который позволяет использовать целочисленные типы в коде:
* uint8_t
* uint32_t
* int32_t
* tuint16_t

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

Это нужно для создания собственных типов с названиями BYTE, LONG, WORD и DWORD. Сам тип определяется исходя из прошлого вопроса

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

1. BYTE - 8 бит
1. LONG - 32 бита
1. WORD - 16 бит
1. DWORD - 32 бита

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

BM 

## What's the difference between `bfSize` and `biSize`?

bfSize = размер всего файла == BITMAPFILEHEADER (14 байт) + BITMAPINFOHEADER (40 байт) + biSizeImage (N байт)
biSize = размер блока BITMAPINFOHEADER == 40 байт

## What does it mean if `biHeight` is negative?

Это значит, что изображение будет строится сверху внизу начиная с верхнего левого края. Так же это значит, что изображение не может быть сжато

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in `copy.c`?

Если в текущей директории нет файла с именем, указанным или в первом или втором параметре. Такое может прозойти из-за ошибки ввода (для infile) или, например, если диск был защищен от записи и файл outfile не создался

## Why is the third argument to `fread` always `1` in our code?

Нужно 1 раз найти и прочитать заданное кол-во байт в заголовках BITMAPFILEHEADER (14) и BITMAPINFOHEADER (40)

## What value does `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

Смещает указатель на заданное количество байт от текущего положения указателя

## What is `SEEK_CUR`?

Возвращает текущее положение указателя в файле
