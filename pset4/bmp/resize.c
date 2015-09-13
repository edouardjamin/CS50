/**
 * M. Adan
 *
 * Computer Science 50
 * PSet 4
 *
 * resize.c
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"


#define BHEADER 54


int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: copy infile outfile\n");
        return 1;
    }

    // resize factor and filenames
    int n = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];

    if (n < 0 || n > 100)
    {
        printf("enter number between 1 and 100 only!\n");
    }

    // open input file
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
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

    // set new dimension for bitmap & calculate
    int firstWidth = bi.biWidth;
    int firstHeight = bi.biHeight;
    bi.biWidth *= n;
    bi.biHeight *= n;

    // padding for scanlines
    int firstPadding = (4 - (firstWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int lastPadding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // calculation of bfSize
    bi.biSizeImage = abs(bi.biHeight) * (bi.biWidth * sizeof(RGBTRIPLE) + lastPadding);
    bf.bfSize = (bi.biSizeImage + BHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);


    // iterate over infile's scanlines
    for (int i = 0; i < abs(firstHeight); i++)
    {
        for (int j = 0; j < n; j++)
        {
            // go over remaing padding
            fseek(inptr, (BHEADER + ((firstWidth * 3 + firstPadding) * i)), SEEK_SET);
            for (int k = 0; k < firstWidth; k++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                for (int l = 0; l < n; l++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // stock last padding
            for (int l = 0; l < lastPadding; l++)
            {
                fputc(0x00, outptr);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
