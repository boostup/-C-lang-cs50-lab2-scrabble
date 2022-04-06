#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define JPEG_BLOCK_SIZE 512
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{

    char *forensicFilename = argv[1];
    FILE *memCardPtr = fopen(forensicFilename, "r");

    //  accept exactly one command-line argument
    if (argc == 1 || argc > 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // check for file pointer
    if (memCardPtr == NULL)
    {
        printf("An error has occured while opening \n");
        return 1;
    }

    // allocating heap memory for an array :
    //  - of elements of type `BYTE`,
    //  - of size = `JPEG_BLOCK_SIZE`
    BYTE *buffer = malloc(JPEG_BLOCK_SIZE);
    // reading forensic file
    int jpegCount = 0;
    char jpegFileName[8];
    FILE *jpegFilePtr = NULL;

    while (fread(buffer, 1, JPEG_BLOCK_SIZE, memCardPtr))
    {
        // DEBUG
        // printf("%02x => %02x\n", buffer[3], buffer[3] & 0xf0);
        // printf("%02x => %02x\n", 0xe5, 0xe5 & 0xf0);

        // checking buffer's first 4 Bytes to detect jpeg headers
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {

            if (jpegCount < 1)
            {
                // setting up a new file name for the detected jpeg
                sprintf(jpegFileName, "%03i.jpg", jpegCount);
                // printf("%s\n", jpegFileName);

                // creating a new file
                jpegFilePtr = fopen(jpegFileName, "w");
                // DEBUG: counting the amount JPEG found. It should be 50
                // printf("#: %i\n", jpegCount);
                jpegCount++;
            }
            else
            {
                fclose(jpegFilePtr);

                sprintf(jpegFileName, "%03i.jpg", jpegCount);
                // printf("%s\n", jpegFileName);

                // creating a new file
                jpegFilePtr = fopen(jpegFileName, "w");
                // DEBUG: counting the amount JPEG found. It should be 50
                // printf("#: %i\n", jpegCount);
                jpegCount++;
            }
            fwrite(buffer, 1, JPEG_BLOCK_SIZE, jpegFilePtr);
        }
        else
        {
            // printf("NOT headerssss\n");
            if (jpegFilePtr != NULL)
                fwrite(buffer, 1, JPEG_BLOCK_SIZE, jpegFilePtr);
        }
    }

    fclose(memCardPtr);
    free(buffer);
}