#include "helpers.h"
#include <math.h>
int maxRGB(int RGB);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //calculate average
            int averageColor = round(((float)image[i][j].rgbtRed + (float)image[i][j].rgbtGreen + (float)image[i][j].rgbtBlue) / 3);
            //reset the RGB to new average
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = averageColor;
        }
    }
    return;
}

//set maximum RGB to 255
int max(int RGB)
{
    if (RGB > 255)
    {
        RGB = 255; 
    }
    return RGB;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //calculate new sepia colors using formula
            int sepiaRed = max(round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue));
            int sepiaGreen = max(round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue));
            int sepiaBlue = max(round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue));

            //set RBG to sepia colors
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //declare variable temp
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            //store the original RGB colors in temp
            temp[i][j] = image[i][j];
            //swap colors to reflect
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp[i][j];
        }
    }
    return;
}

// Blur image 
//Collaborator: William Yao 
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //declare variable temp
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < height; j++)
        {
            //store original RGB colors in temp
            temp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // initialize variables
            int valid_pixel = 0;
            int sumRed = 0;
            int sumBlue = 0;
            int sumGreen = 0;

            for (int a = -1; a <= 1; a++)
            {
                for (int b = -1; b <= 1; b++)
                {
                    //make sure that the pixels are valid and exist in the 3x3 frame
                    if ((a + i) >= 0 && (a + i) <= (height - 1) && (b + j) >= 0 && (b + j) <= (width - 1))
                    {
                        //add valid pixel to counter 
                        valid_pixel++;
                        //calculate the sum of RGB colors for valid pixels
                        sumRed += temp[a + i][b + j].rgbtRed;
                        sumGreen += temp[a + i][b + j].rgbtGreen;
                        sumBlue += temp[a + i][b + j].rgbtBlue;
                    }
                }
            }
            //set the average colors as the new RGB colors
            image[i][j].rgbtRed = round(sumRed * 1.0 / valid_pixel);
            image[i][j].rgbtGreen = round(sumGreen * 1.0 / valid_pixel);
            image[i][j].rgbtBlue = round(sumBlue * 1.0 / valid_pixel);
        }
    }
    return;
}
