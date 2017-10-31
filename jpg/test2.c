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
    
    // a buffer of 512 bytes
    char buffer[1];
    
    fread(buffer, sizeof(buffer), 1, inptr);

    // buffer[0] = 0x11;
        
        
    if(buffer[0] == 0xff){
        printf("C!!!!!!");
    }

    
    return 0;
}

