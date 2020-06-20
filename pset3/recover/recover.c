#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // проверяем, что введёт только 1 аргумент
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // создаём переменную input_file для входящего файла, открываем этот файл и получаем его указатель в переменную inputer
    char *input_file = argv[1];
    FILE *inputer = fopen(input_file, "r");
    FILE *outputer = NULL;
    int file_name = -1;
    char full_file_name[9];
    sprintf(full_file_name, "%03i.jpg", file_name);
    int counter = 0;

    // проверяем, что файл открылся
    if (inputer == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", input_file);
        return 2;
    }
    // задали буфер - массив размером 512 индексов по 1 байту
    uint8_t buffer[512];
    // начинаем движение от начала файла до eof от кластера к кластеру
    while (fread(&buffer, 512, 1, inputer) > 0) // printf("Считал новые 512 байт из исходного файла\n");
    {
        // ищет шаблон, характерный для начала jpg файла, в начале кластера
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] >= 0xe0 || buffer[3] >= 0xef))
        {
            if (counter > 0)
            {
                fclose(outputer);  // printf("Закрыл предыдущий файл\n"), потому что counter показывает, что файлы открывались;

            }
            file_name++;
            sprintf(full_file_name, "%03i.jpg", file_name);
            outputer = fopen(full_file_name, "w"); // printf("Создал новый файл %i\n", file_name);
            // проверяем, что файл существует
            if (outputer == NULL)
            {
                fprintf(stderr, "Could not open %s.\n", full_file_name);
                return 3;
            }

            counter++;
        }
        if (counter > 0)
        {
            fwrite(&buffer, 512, 1, outputer);
            // printf("Записал 512 байт в файл %i\n", file_name), так как counter показывает, что файлы начали открываться;
        }
    }
    // закрываем файлы
    fclose(outputer);
    // printf("Закрыл предыдущий файл\n");
    fclose(inputer);
    // printf("Закрыл изначальный файл\n");
    return 0;
}
