// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

// Number of bytes for samples
const int SAMPLE_SIZE = 2;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Copy header from input file to output file
    uint8_t header[HEADER_SIZE];

    if (fread(&header, HEADER_SIZE, 1, input))
    {
        fwrite(&header, HEADER_SIZE, 1, output);
    }

    // printf("sizeof(uint8_t): %lu\tHEADER_SIZE: %i\n", sizeof(uint8_t), HEADER_SIZE);

    // Read samples from input file and write updated data to output file
    int16_t buffer;

    // `fread` reads from where it left of during the last `fread` call, meaning when the 44-bytes header was read and copied to the output wave file.
    while (fread(&buffer, SAMPLE_SIZE, 1, input))
    {
        buffer = buffer * factor;
        fwrite(&buffer, SAMPLE_SIZE, 1, output);
    }

    // printf("sizeof(int16_t): %lu\tSAMPLE_SIZE: %i\n", sizeof(int16_t), SAMPLE_SIZE);

    // Close files
    fclose(input);
    fclose(output);
}
