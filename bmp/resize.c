/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy n infile outfile\n");
        return 1;
    }

    // remember filenames
    char* increaseSizeString = argv[1];
    int increaseSize = atoi(increaseSizeString);
    char* infile = argv[2];
    char* outfile = argv[3];
    
    if(increaseSize < 0 || increaseSize > 100)
    {
        printf("The resize factor should be a positive int.\n");
        return 2;
    }

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
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

    long oldWidth = bi.biWidth;
    long oldHeight = bi.biHeight;
    
    // Construsct bitmap headers for out file
    // ??????
    
    bi.biWidth = oldWidth * increaseSize;
    bi.biHeight = oldHeight * increaseSize;
    
    // determine padding for scanlines
    int padding =  (4 - (oldWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int newPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    bf.bfSize = 54 + bi.biWidth * abs(bi.biHeight) * 3 + abs(bi.biHeight) *  newPadding;
	bi.biSizeImage = ((((bi.biWidth * bi.biBitCount) + 31) & ~31) / 8) * abs(bi.biHeight);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    
    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int row = 0, biHeight = labs(oldHeight); row < biHeight; row++)
    {
        // repeate each line already drawn
        for (int repeat = 0; repeat < increaseSize; repeat++)
        {
            // iterate over pixels in scanline
            for (int col = 0; col < oldWidth; col++)
            {
                // temporary storage
                RGBTRIPLE triple;
    
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                for(int draw = 0; draw < increaseSize; draw++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
                    
            }
        
            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);
    
            // then add it back (to demonstrate how)
            for (int k = 0; k < newPadding; k++)
            {
                fputc(0x00, outptr);
            }
            
            fseek(inptr, - (oldWidth * 3 + padding), SEEK_CUR);
        }

        fseek(inptr, oldWidth * 3 + padding, SEEK_CUR);
    }
    
    
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
