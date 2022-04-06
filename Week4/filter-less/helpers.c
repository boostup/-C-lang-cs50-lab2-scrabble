#include <stdio.h>
#include "math.h"
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width,
               RGBTRIPLE image[height][width])
{
    // printf("height:%i, width:%i\n", height, width);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // printf("rgbtRed:%d\r", image[i][j].rgbtRed);
            // printf("rgbtGreen:%d\r", image[i][j].rgbtGreen);
            // printf("rgbtBlue:%d\r", image[i][j].rgbtBlue);
            RGBTRIPLE *pxPtr = &image[i][j];
            int avg = round((pxPtr->rgbtRed + pxPtr->rgbtGreen + pxPtr->rgbtBlue) / 3.0);
            // printf("avg :%i (R:%i,G:%i,B:%i)\n", avg, pxPtr->rgbtRed, pxPtr->rgbtGreen, pxPtr->rgbtBlue);
            pxPtr->rgbtRed = avg;
            pxPtr->rgbtGreen = avg;
            pxPtr->rgbtBlue = avg;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            RGBTRIPLE *pxPtr = &image[i][j];

            float newRed = .393 * pxPtr->rgbtRed + .769 * pxPtr->rgbtGreen + .189 * pxPtr->rgbtBlue;
            float newGreen = .349 * pxPtr->rgbtRed + .686 * pxPtr->rgbtGreen + .168 * pxPtr->rgbtBlue;
            float newBlue = .272 * pxPtr->rgbtRed + .534 * pxPtr->rgbtGreen + .131 * pxPtr->rgbtBlue;

            // printf("R:%i,G:%i,B:%i\n", pxPtr->rgbtRed, pxPtr->rgbtGreen, pxPtr->rgbtBlue);
            // printf("new R:%i,G:%i,B:%i\n", newRed, newGreen, newBlue);

            pxPtr->rgbtRed = fmin(255, round(newRed));
            pxPtr->rgbtGreen = fmin(255, round(newGreen));
            pxPtr->rgbtBlue = fmin(255, round(newBlue));
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    // Temporary image array to hold the inverted pixels per row
    RGBTRIPLE tmpImage[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // left px
            tmpImage[i][j] = image[i][width - 1 - j];

            // right px
            tmpImage[i][width - 1 - j] = image[i][j];
        }
    }

    // replace each pixel by replacing values at pointers [i][j] of `image` array received via arguments of function
    // Note : because I have to write at memory locations in the `image` array, I cannot do the pixel inversion within the previous loop, because if I do, the resulting image is one that reflects only half of the total picture width.  Although it creates an interesting effect, it is not what the assignment is asking for.
    // Therefore, the actual pixel replacement take place in the following loop, achieving full width pixel inversion
    // I've spent about an hour trying to see how I could manage this in one single loop, but because of the required use of pointers to modify the contents of `image` array, this algorithm is the best I can come up with.
    // Downside : although this works, I'm doubling the execution time of this function since this second pair of nested loops is traversing the entire 2D image array again...
    // Upside: code is cleaner to read, and therefore more maintainable...
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE *pxPtr = &image[i][j]; // pointing at the px address in memory
            *pxPtr = tmpImage[i][j];         // dereferencing pointer, so that the assignment changes the value being pointed at, and not the value of the address stored in the pointer variable
        }
    }

    return;
}

RGBTRIPLE get_px_avg_val(int x, int y, int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE avg;
    int redSum = 0, greenSum = 0, blueSum = 0;
    int minI, maxI, minJ, maxJ;

    // determining range for rows for outer loop
    minI = fmax(0, x - 1);
    maxI = fmin(height - 1, x + 1);

    // determining range for cols for inner loop
    minJ = fmax(0, y - 1);
    maxJ = fmin(width - 1, y + 1);

    // printf("*****\nfor(%i,%i) => rows(%i - %i) cols(%i - %i)\t", y, x, minI, maxI, minJ, maxJ);

    // the number of surrounding pixels that will actually be available to calculate the average
    int px_count = 0;

    for (int i = minI; i <= maxI; i++) // rows
    {
        for (int j = minJ; j <= maxJ; j++) // cols
        {
            RGBTRIPLE tmp = image[i][j];
            redSum += tmp.rgbtRed;
            greenSum += tmp.rgbtGreen;
            blueSum += tmp.rgbtBlue;
            px_count++;
        }
    }

    // printf("\n");
    // printf("px_count: %i\n", px_count);
    // printf("red avg: %f | %f\n", round((float)redSum / px_count), round((float)avg.rgbtRed / px_count));

    avg.rgbtRed = round((float)redSum / px_count);     // casting to float so that the integer round passes `check50`
    avg.rgbtGreen = round((float)greenSum / px_count); // casting to float so that the integer round passes `check50`
    avg.rgbtBlue = round((float)blueSum / px_count);   // casting to float so that the integer round passes `check50`
    return avg;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    // Creating copy of image array to avoid pixel manipulation overlaps
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // `Test suite`
    // RGBTRIPLE avg;
    // avg = get_px_avg_val(0, 0, height, width, copy);
    // // printf("R %i, G %i, B %i\n", avg.rgbtRed, avg.rgbtGreen, avg.rgbtBlue);

    // avg = get_px_avg_val(1, 3, height, width, copy);
    // // printf("R %i, G %i, B %i\n", avg.rgbtRed, avg.rgbtGreen, avg.rgbtBlue);

    // avg = get_px_avg_val(2, width - 1, height, width, copy);
    // // printf("R %i, G %i, B %i\n", avg.rgbtRed, avg.rgbtGreen, avg.rgbtBlue);

    // avg = get_px_avg_val(height - 1, 0, height, width, copy);
    // // printf("R %i, G %i, B %i\n", avg.rgbtRed, avg.rgbtGreen, avg.rgbtBlue);

    // looping through all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // get the average value for current pixel
            RGBTRIPLE *pxPtr = &image[i][j];
            *pxPtr = get_px_avg_val(i, j, height, width, copy);
        }
    }

    return;
}
