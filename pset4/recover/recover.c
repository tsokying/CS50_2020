#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

const int Block = 512;
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //Usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    //Open the memory card
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        printf("Image cannot be opened for reading\n");
        return 1;
    }

    BYTE buffer[Block];
    int fileNumber = 0;
    char filename[8];
    FILE *outptr = NULL;
    bool found = false;

    //Repeat until end of card
    while (fread(buffer, Block, 1, inptr))
    {
        //Check jpeg beginning
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //If not first jpg
            if (found == true)
            {
                fclose(outptr);
            }
            else
            {
                found = true;
            }
            sprintf(filename, "%03i.jpg", fileNumber);
            outptr = fopen(filename, "w");
            fileNumber++;
        }
        if (found == true)
        {
            fwrite(buffer, Block, 1, outptr);
        }
    }
    //Close any remaining files
    fclose(outptr);
    fclose(inptr);
    return 0;
}
