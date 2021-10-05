#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// prototyes
// RGBTRIPLE neighbor_avg(int row_start,int row_end,int column_start,int column_end, RGBTRIPLE image[rows][columns]);


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // loop through rows
    for (int i = 0; i < height; i++)
    {
        // loop through cells
        for (int j = 0; j < width; j++)
        {
            // take average of current rgb values
            float avg = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;
            avg = (int)round(avg);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Flip the row, hit em with a swap
    for (int i = 0; i < height; i++)
    {
        RGBTRIPLE tmp;
        for (int j = 0; j < width / 2; j++)
        {
            tmp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // temp array to store new rgb values
    RGBTRIPLE img_cp[height][width];

    float red_avg, green_avg, blue_avg;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // inner loop to get avgs
            red_avg = green_avg = blue_avg = 0;
            int counter = 0;
            for (int n = i - 1; n < i + 2; n++)
            {
                // first row edge case
                if (n < 0)
                {
                    n = i;
                }
                // last row edge case
                else if (n == height)
                {
                    break;
                }

                for (int m = j - 1; m < j + 2; m++)
                {
                    // first column edge case
                    if (m < 0)
                    {
                        m = j;
                    }
                    // last column edge case
                    else if (m == width)
                    {
                        break;
                    }
                    red_avg = red_avg + image[n][m].rgbtRed;
                    green_avg = green_avg + image[n][m].rgbtGreen;
                    blue_avg = blue_avg + image[n][m].rgbtBlue;
                    counter++;
                }
            }
            red_avg = red_avg / counter;
            green_avg = green_avg / counter;
            blue_avg = blue_avg / counter;
            img_cp[i][j].rgbtRed = (int)round(red_avg);
            img_cp[i][j].rgbtGreen = (int)round(green_avg);
            img_cp[i][j].rgbtBlue = (int)round(blue_avg);
        }
        // // debuging
        // printf("I am on row: %i\n", i);
    }
    // Write new RGB Triple array to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = img_cp[i][j];
        }
    }
    return;

}


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // temp RGB matrix to store new rgb values
    RGBTRIPLE img_cp[height][width];

    // initiate gx and gy matrix
    int gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int gy[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };
    double red_gx, red_gy, green_gx, green_gy, blue_gx, blue_gy, new_red, new_green, new_blue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // inner loop to get gx and gy values
            red_gx = red_gy = green_gx = green_gy = blue_gx = blue_gy = new_red = new_green = new_blue = 0;
            int counter = 0;
            for (int n = i - 1; n < i + 2; n++)
            {
                // first row edge case
                if (n < 0)
                {
                    continue;
                }
                // last row edge case
                else if (n == height)
                {
                    break;
                }

                for (int m = j - 1; m < j + 2; m++)
                {
                    // first column edge case
                    if (m < 0)
                    {
                        continue;
                    }
                    // last column edge case
                    else if (m == width)
                    {
                        break;
                    }
                    red_gx = red_gx + image[n][m].rgbtRed * gx[n - i + 1][m - j + 1];
                    red_gy = red_gy + image[n][m].rgbtRed * gy[n - i + 1][m - j + 1];
                    green_gx = green_gx + image[n][m].rgbtGreen * gx[n - i + 1][m - j + 1];
                    green_gy = green_gy + image[n][m].rgbtGreen * gy[n - i + 1][m - j + 1];
                    blue_gx = blue_gx + image[n][m].rgbtBlue * gx[n - i + 1][m - j + 1];
                    blue_gy = blue_gy + image[n][m].rgbtBlue * gy[n - i + 1][m - j + 1];

                    counter++;
                }
            }
            new_red = sqrt((red_gx * red_gx) + (red_gy * red_gy));
            new_green = sqrt((green_gx * green_gx) + (green_gy * green_gy));
            new_blue = sqrt((blue_gx * blue_gx) + (blue_gy * blue_gy));
            // max pixel value
            if (new_red > 255)
            {
                new_red = 255;
            }
            if (new_green > 255)
            {
                new_green = 255;
            }
            if (new_blue > 255)
            {
                new_blue = 255;
            }
            img_cp[i][j].rgbtRed = (int)round(new_red);
            img_cp[i][j].rgbtGreen = (int)round(new_green);
            img_cp[i][j].rgbtBlue = (int)round(new_blue);
        }
        // // debuging
        // printf("I am on row: %i\n", i);
    }
    // Write new RGB Triple array to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = img_cp[i][j];
        }
    }
    return;
}
