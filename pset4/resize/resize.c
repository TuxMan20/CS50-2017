/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Resizes a BMP into a new file.
 */
        
#include <stdio.h>
#include <stdlib.h>
 
#include "bmp.h"
 
int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize size infile outfile\n");
        return 1;
    }
 
    // remember size & filenames
    int size = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];
     
    if(size < 1 || size > 100)
    {
        printf("Usage: Resize must be between 1 and 100");
        return 1;
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
     
//Most of the work happens below this point//
 
    //Initializes new headers that will be resized and used for the Out File
    BITMAPFILEHEADER bfout = bf;
    BITMAPINFOHEADER biout = bi;
     
    // calculates resized width and height for the Info Header
    biout.biWidth = bi.biWidth * size;
    biout.biHeight = bi.biHeight * size;
     
    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int paddingout = (4 - (biout.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
     
    //calculates new size of image
    biout.biSizeImage = (biout.biWidth * sizeof(RGBTRIPLE) + paddingout) * abs(biout.biHeight);
     
     //calculating bfSize, courtesy of StackOverflow.com
    bfout.bfSize = bf.bfSize - bi.biSizeImage + biout.biSizeImage;
     
    // write outfile's BITMAPFILEHEADER
    fwrite(&bfout, sizeof(BITMAPFILEHEADER), 1, outptr);
 
    // write outfile's BITMAPINFOHEADER
    fwrite(&biout, sizeof(BITMAPINFOHEADER), 1, outptr);
 
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        //moving the cursor, found on /r/cs50
        fpos_t pos;
        fgetpos (inptr, &pos);
     
        for(int k = 0; k < size; k++) //makes sure scan lines are repeated vertically
        {
         
            if(k < size) 
                fsetpos(inptr, &pos);
                 
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
 
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                 
                // write RGB triple to outfile, once per value of "size"
                 
                for(int l = 0; l < size; l++)
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr); //copies pixels of the scan line
            }
 
            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);
 
            // then add it back 
            for (int l = 0; l < paddingout; l++)
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