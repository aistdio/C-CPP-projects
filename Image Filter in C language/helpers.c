#include "helpers.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// typedef struct
// {
//     BYTE  rgbtBlue;
//     BYTE  rgbtGreen;
//     BYTE  rgbtRed;
// } __attribute__((__packed__))
// RGBTRIPLE;

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            int a = round((round(image[i][k].rgbtBlue) + round(image[i][k].rgbtGreen) + round(image[i][k].rgbtRed)) / 3);

            image[i][k].rgbtBlue = a;
            image[i][k].rgbtGreen = a;
            image[i][k].rgbtRed = a;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            int sepiaBlue = round(0.272 * image[i][k].rgbtRed + 0.534 * image[i][k].rgbtGreen + 0.131 * image[i][k].rgbtBlue);
            int sepiaGreen = round(0.349 * image[i][k].rgbtRed + 0.686 * image[i][k].rgbtGreen + 0.168 * image[i][k].rgbtBlue);
            int sepiaRed = round(0.393 * image[i][k].rgbtRed + 0.769 * image[i][k].rgbtGreen + 0.189 * image[i][k].rgbtBlue);
            int *b = &sepiaBlue;
            int *g = &sepiaGreen;
            int *r = &sepiaRed;
            if (*b > 255)
            {
                *b = 255;
            }
            if (*g > 255)
            {
                *g = 255;
            }
            if (*r > 255)
            {
                *r = 255;
            }
            image[i][k].rgbtBlue = *b;
            image[i][k].rgbtGreen = *g;
            image[i][k].rgbtRed = *r;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmpB[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k <= round(width/2); k++)
        {
            tmpB[i][k] = image[i][k];
            image[i][k] = image[i][width - 1 - k];
        }
        for (int k = 0; k <= round((width-1)/2); k++)
        {
            image[i][width - 1 - k] = tmpB[i][k];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE color[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            color[i][k] = image[i][k];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            float counter = 0.00;
            int Red = 0, Blue = 0, Green = 0;

            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    int currentX = i + x;
                    int currentY = k + y;

                    if (currentX < 0 || currentY < 0 || currentX > (height - 1) || currentY > (width - 1))
                    {
                        continue;
                    }
                    Red += image[currentX][currentY].rgbtRed;
                    Blue += image[currentX][currentY].rgbtBlue;
                    Green += image[currentX][currentY].rgbtGreen;

                    counter++;
                }
            }
            color[i][k].rgbtRed = round(Red / counter);
            color[i][k].rgbtGreen = round(Green / counter);
            color[i][k].rgbtBlue = round(Blue / counter);
        }
    }
    for (int i = 0; i < height; i++)
        {
            for (int k = 0; k < width; k++)
            {
                image[i][k] = color[i][k];
            }
        }
    return;
}
