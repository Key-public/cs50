// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // remember n and filenames
    int n = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    // ensure proper usage
    if (argc != 4 || n < 1 || n >= 100)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }



    // поменять настройки конечного файла перед записью
    bi.biWidth *= n;
    bi.biHeight *= n;

    // determine padding for scanlines
    int inptr_padding = (4 - (bi.biWidth / n * sizeof(RGBTRIPLE)) % 4) % 4;
    int outptr_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // вернуться к изменению заголовков
    int biHeight = abs(bi.biHeight);
    bi.biSizeImage = bi.biWidth * biHeight * sizeof(RGBTRIPLE) + outptr_padding * biHeight;
    bf.bfSize = 54 + bi.biSizeImage;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0; i < biHeight / n; i++)
    {
        int counter = 0;
        for (int l = 0; l < n; l++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth / n; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                for (int m = 0; m < n; m++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }


            // skip over padding, if any
            fseek(inptr, inptr_padding, SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int k = 0; k < outptr_padding; k++)
            {
                fputc(0x00, outptr);
            }

            // N раз перемещает указатель назад, чтобы скопировать пиксели в строке

            if (counter < n - 1)
            {
                fseek(inptr, -(bi.biWidth / n * sizeof(RGBTRIPLE) + inptr_padding), SEEK_CUR);
                counter++;
            }
        }

    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
