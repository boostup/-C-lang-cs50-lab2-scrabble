#include <cs50.h>
#include <stdio.h>
#include <string.h>

int getPyramidSize();
void builPyramidOfSize(int size);

int main(void)
{
    int pyramidSize = getPyramidSize();
    builPyramidOfSize(pyramidSize);
}

/**
 * Asks for the size of the pyriamid to build
 * @return the integer value of the input
 */

int getPyramidSize()
{

    int input = 0;
    do
    {
        input = get_int("Choose a pyramid size (between 1 - 8): ");
    } //
    while (input < 1 || input > 8);

    return input;
}

/**
 * Prints a pyramid according to specifications
 * @param int size. this is to specify the number of levels composing the pyramid
 * @return void.  prints to the console
 */
void builPyramidOfSize(int size)
{
    string blockSpace = " ";
    string block = "#";

    for (int i = 0; i < size; i++)
    {
        // printing spaces for line `i`
        for (int y = 0; y < size - i - 1; y++)
        {
            printf("%s", blockSpace);
        }

        // printing blocks for line `i`, for LEFT side
        for (int y = -1; y < size - (size - i); y++)
        {
            printf("#");
        }

        // printing middle separation
        printf("%s%s", blockSpace, blockSpace);

        // printing blocks for line `i`, for Right side
        for (int y = -1; y < size - (size - i); y++)
        {
            printf("%s", block);
        }

        printf("\n");
    }
}
