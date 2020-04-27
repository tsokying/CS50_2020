#include <math.h>
#include <stdlib.h>

#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int Grey;
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            Grey = round((image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed) / 3.0);
            image[h][w].rgbtBlue = Grey;
            image[h][w].rgbtGreen = Grey;
            image[h][w].rgbtRed = Grey;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for (int h = 0; h < height; h++)
    {
        //Stop at Middle
        for (int w = 0; w < width / 2; w++)
        {
            //Swap
            temp = image[h][w];
            image[h][w] = image[h][width - 1 - w];
            image[h][width - 1 - w] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int SumBlue, SumGreen, SumRed;
    float neighbour; // float, in order to round() correctly
    RGBTRIPLE temp[height][width];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            SumBlue = 0, SumGreen = 0, SumRed = 0, neighbour = 0;
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    //Skip if out of image
                    if (h + i < 0 || h + i > height - 1 || w + j < 0 || w + j > width - 1)
                    {
                        continue;
                    }

                    SumBlue += image[h + i][w + j].rgbtBlue;
                    SumGreen += image[h + i][w + j].rgbtGreen;
                    SumRed += image[h + i][w + j].rgbtRed;
                    neighbour++;
                }
            }
            //Store in temp
            temp[h][w].rgbtBlue = round(SumBlue / neighbour);
            temp[h][w].rgbtGreen = round(SumGreen / neighbour);
            temp[h][w].rgbtRed = round(SumRed / neighbour);
        }
    }
    //Paste to output
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w].rgbtBlue = temp[h][w].rgbtBlue;
            image[h][w].rgbtGreen = temp[h][w].rgbtGreen;
            image[h][w].rgbtRed = temp[h][w].rgbtRed;
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    float SumBlueX, SumGreenX, SumRedX, SumBlueY, SumGreenY, SumRedY;
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    RGBTRIPLE temp[height][width];

    for (int w = 0; w < width; w++)
    {
        for (int h = 0; h < height; h++)
        {
            SumBlueX = 0.0, SumGreenX = 0.0, SumRedX = 0.0, SumBlueY = 0.0, SumGreenY = 0.0, SumRedY = 0.0;
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    //Skip if out of image
                    if (h + i < 0 || h + i > height - 1 || w + j < 0 || w + j > width - 1)
                    {
                        continue;
                    }

                    SumBlueX += image[h + i][w + j].rgbtBlue * Gx[i + 1][j + 1];
                    SumGreenX += image[h + i][w + j].rgbtGreen * Gx[i + 1][j + 1];
                    SumRedX += image[h + i][w + j].rgbtRed * Gx[i + 1][j + 1];

                    SumBlueY += image[h + i][w + j].rgbtBlue * Gy[i + 1][j + 1];
                    SumGreenY += image[h + i][w + j].rgbtGreen * Gy[i + 1][j + 1];
                    SumRedY += image[h + i][w + j].rgbtRed * Gy[i + 1][j + 1];
                }
            }

            //Applying formula and cap at 255
            int temp_blue = round(sqrt(SumBlueX * SumBlueX + SumBlueY * SumBlueY));
            if (temp_blue > 255)
            {
                temp_blue = 255;

            }
            int temp_green = round(sqrt(SumGreenX * SumGreenX + SumGreenY * SumGreenY));
            if (temp_green > 255)
            {
                temp_green = 255;
            }
            int temp_red = round(sqrt(SumRedX * SumRedX + SumRedY * SumRedY));
            if (temp_red > 255)
            {
                temp_red = 255;

            }

            temp[h][w].rgbtBlue = temp_blue;
            temp[h][w].rgbtGreen = temp_green;
            temp[h][w].rgbtRed = temp_red;

        }
    }

    //Paste to output
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w].rgbtBlue = temp[h][w].rgbtBlue;
            image[h][w].rgbtGreen = temp[h][w].rgbtGreen;
            image[h][w].rgbtRed = temp[h][w].rgbtRed;
        }
    }

    return;
}