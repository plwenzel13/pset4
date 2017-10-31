/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
 
#include <stdio.h>
#include <stdlib.h>
// For defining various integer types. 
#include <stdint.h>

// 8-bit unsigned type aka: Unsigned, 8 Bits, 1 Bytes, 0 Minimum Value, 28 − 1 which equals 255 Maximum Value
typedef uint8_t BYTEBUF;

int main(int argc, char* argv[])
{
    // open card file 
    FILE* inptr = fopen("card.raw", "r");
    if (inptr == NULL)
    {
        fclose(inptr);
        printf("Could not open card.raw");
        return 1;
    }
    
    // initliaze counter
    int counter = 0;
    
    // a buffer of 512 bytes
    BYTEBUF buffer[512];
    
    // output file three-digit number from 000 on up.
    char outfile[30];
    
    // file out temp storage
    FILE* temp = NULL;

    // repeat until end of card
    // read form inptr file
    while (fread(buffer, sizeof(buffer), 1, inptr) != 0)
    {
        // check to see if start of jpg file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            // if start of a new jpg? NO
            if (temp != NULL)
            {
                fclose(temp);
            }
            
            // if start of a new jpg? YES
            sprintf(outfile, "%03d.jpg", counter);
            
            // find next jpg in file
            temp = fopen(outfile, "w");
            
            // increase name of file by one
            counter++;
            
            // write new file with buffer
            fwrite(buffer, sizeof(buffer), 1, temp);
        }
        // else already found a jpg
        else if (counter > 0)
        {
            // put jpg info into temp
            fwrite(buffer, sizeof(buffer), 1, temp);
        }
        // repeat until end of card
        else if (feof(inptr))
        {
            fwrite(buffer, sizeof(buffer), 1, temp);
        }
    }
    // close the file
    fclose(temp);

    return 0;
}

