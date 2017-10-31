/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
 //pseudocode:
 //open card file
 //repeat until end of card
    //while - read 512 bytes into a buffer
    //if start of a new jpg?
        //yes -> ...
        //no -> ...
    //else alread found a jpg?
        //no -> ...
        //yes -> ...
 //close any remaining files
 
#include <stdio.h>
#include <stdlib.h>

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
    char buffer[512];
    
    // output file three-digit number from 000 on up.
    char outfile[30];
    
    // file out temp storage
    FILE* temp = NULL;
   // char c = 'a';
    //int i = 0;
    
    // repeat until end of card
    while (!feof(inptr))
    {
        fread(buffer, sizeof(buffer), 1, inptr);
        //printf("%d\n", i++);
        //if (1 == 2)
         //{

        // check to see if start of jpg file
        //printf("after fread\n"); //working
        
        //printf("buffer 0: %0x, buffer 1: %0x, buffer 2: %0x, buffer 3: %0x\n", buffer[0], buffer[1], buffer[2], buffer[3]);
        
        
        //if (buffer == 0xff, 0xd8, 0xff, 0xe0 || 0xff, 0xd8, 0xff, 0xe1) 
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            
            printf("Start of new file\n");
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
            printf("if counter > 0\n");
            // put jpg info into temp
            fwrite(buffer, sizeof(buffer), 1, temp);
            
        }
        // read outfile
        printf("pre-read outfile\n");

        //fread(buffer, sizeof(buffer), 1, );
       // printf("read outfile\n");

   // }
    }

    // // open output file
    // FILE* outptr = fopen(outfile, "w");
    // if (outptr == NULL)
    // {
    //     fclose(inptr);
    //     fprintf(stderr, "Could not create %s.\n", outfile);
    //     return 2;
    // }
    
    // close the file
    //fclose(temp);
    
    // free malloc
    //free(buffer);
    
    return 0;
}

