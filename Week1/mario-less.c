#include <cs50.h>
#include <stdio.h>

void drawPyramidLeftAlign(int height);
void drawPyramidRightAlign(int height);

int main(void)
{
    int pyramidHeight = 0;
    do
    {
        pyramidHeight = get_int("Height of pyramid (between 1 - 8): ");
    } while (pyramidHeight < 1 || pyramidHeight > 8);

    // printf("height: %i\n", pyramidHeight);

    drawPyramidRightAlign(pyramidHeight);
}

void drawPyramidLeftAlign(int height)
{
    for (int i = 1; i < height + 1; i++)
    {
        for (int y = 0; y < i; y++)
        {
            printf("#");
        }
        printf("\n");
    }
}
void drawPyramidRightAlign(int height)
{
    for (int i = 1; i < height + 1; i++)
    {
        // print spaces
        for (int y = 0; y < height - i; y++)
        {
            printf(" ");
        }
        // print dashes
        for (int y = 0; y < i; y++)
        {
            printf("#");
        }
        printf("\n");
    }
}