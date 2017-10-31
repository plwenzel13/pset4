#include <stdio.h>
#include <stdlib.h>

//#include "bmp.h"

int main(int argc, char* argv[])
{
    char buffer[1];
    buffer[0] = 0x11;
    
    if(buffer[0] == 0x12)
    {
        printf("c is killing me!\n");
    }
    return 0;
}