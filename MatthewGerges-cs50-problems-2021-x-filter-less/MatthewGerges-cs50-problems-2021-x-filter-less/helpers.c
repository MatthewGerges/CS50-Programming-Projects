#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <cs50.h>
//include math.h for rouding

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //image is of data type RGB triple which contains the bytes rgbtblue, rgbtred and rgbtgreen as defined in bmp.h

    //iterate through every column of pixels
    for (int i = 0; i < height; i++)
    {
        //iterate through all the pixels in that column one by one
        //once all the pixels are done, break out of the j loop and go to the i loop, moving to the next column
        for (int j = 0; j < width; j++)
        {
            //the bytes of red, green and blue in an image are integers
            int b = image[i][j].rgbtBlue;
            int r = image[i][j].rgbtRed;
            int g = image[i][j].rgbtGreen;

            //compute the average which is a float of the 0-255 value of the amount of red, green, and blue in each pixel
            float average = ((float)r + (float)b + (float)g) / 3;
            //round the average to the nearest whole number (bytes of blue, red, and green are integers)
            average = round(average);

            image[i][j].rgbtBlue = average;
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;

        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{   //iterate through every column
    for (int i = 0; i < height; i++)
    {
        //iterate through every pixel in the column
        for (int j = 0; j < width; j++)
        {
            int b = image[i][j].rgbtBlue;
            int r = image[i][j].rgbtRed;
            int g = image[i][j].rgbtGreen;

            //calculate the sepia formulas
            float sblue = round(0.272 * r + 0.534 * g + 0.131 * b);
            float sred = round(0.393 * r + 0.769 * g + 0.189 * b);
            float sgreen = round(0.349 * r + 0.686 * g + 0.168 * b);

            //if the sepia formulas exceed values of 255, round them down t0 255
            if (sblue > 255)
                sblue = 255;
            if (sred > 255)
                sred = 255;
            if (sgreen > 255)
                sgreen = 255;

            //set the rgbt colours to the newly calculated sepia colours
            image[i][j].rgbtBlue = sblue;
            image[i][j].rgbtRed = sred;
            image[i][j].rgbtGreen = sgreen;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //swap pixels on horizontally opposite sides
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width/2; j++)
        {
            //we subtract 1 from the width because we would be out of the bounds of the array if we didn't
            int tempb = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width-1-j].rgbtBlue;
            image[i][width-1-j].rgbtBlue = tempb;

            int tempr = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width -1 - j].rgbtRed;
            image[i][width-1-j].rgbtRed = tempr;

            int tempg = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width-1-j].rgbtGreen;
            image[i][width-1-j].rgbtGreen = tempg;
        }

    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp[i][j] = image[i][j];
        }
    }
    //temp [i][j] = image [i][j]; maybe mistake
    
    int R = 0;
    int Rright = 0;
    int Rleft = 0;
    int Rup = 0;
    int Rupr = 0;
    int Rupl = 0;
    int Rdown = 0;
    int Rdownr = 0;
    int Rdownl = 0;
    
    int G = 0;
    int Gright = 0;
    int Gleft = 0;
    int Gup = 0;
    int Gupr = 0;
    int Gupl = 0;
    int Gdown = 0;
    int Gdownr = 0;
    int Gdownl = 0;
    
    int B = 0;
    int Bright = 0;
    int Bleft = 0;
    int Bup = 0;
    int Bupr = 0;
    int Bupl = 0;
    int Bdown = 0;
    int Bdownr = 0;
    int Bdownl = 0;
    
    
    //initialize the following to 0?
    //put the following in the for loop?
    float Ravg = 0;
    float Bavg = 0;
    float Gavg = 0;


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < height; j++)
        {
            //if there is a left, if there is a right, if there is an up
            //is it becuse these are not specific and b/c there should be a sumred, sumblue, sungreen?
            if (j > 0)
            {
                 Rleft = tmp[i][j - 1].rgbtRed;
                 Gleft = tmp[i][j - 1].rgbtGreen;
                 Bleft = tmp[i][j - 1].rgbtBlue;
            }
            
            else
            {
                 Rleft = 0;
                 Gleft = 0;
                 Bleft = 0;
            }
            
            if (j < width - 1)
            {
                 Rright = tmp[i][j + 1].rgbtRed;
                 Gright = tmp[i][j + 1].rgbtGreen;
                 Bright = tmp[i][j + 1].rgbtBlue;
            }
            
            else
            {
                 Rright = 0;
                 Gright = 0;
                 Bright = 0;
            }
            
            if (i > 0)
            {
                 Rup = tmp[i - 1][j].rgbtRed;
                 Gup = tmp[i - 1][j].rgbtGreen;
                 Bup = tmp[i - 1][j].rgbtBlue;
            }
            
            else
            {
                 Rup = 0;
                 Gup = 0;
                 Bup = 0;
            }
            
            if (j < width - 1 && i > 0)
            {
                 Rupr = tmp[i - 1][j + 1].rgbtRed;
                 Gupr = tmp[i - 1][j + 1].rgbtGreen;
                 Bupr = tmp[i - 1][j + 1].rgbtBlue;
            }
            
            else
            {
                 Rupr = 0;
                 Gupr = 0;
                 Bupr = 0;
            }
            
            if ( i > 0 && j > 0)
            {
                 Rupl = tmp[i - 1][j - 1].rgbtRed;
                 Gupl = tmp[i - 1][j - 1].rgbtGreen;
                 Bupl = tmp[i - 1][j - 1].rgbtBlue;
            }
            
            else
            {
                 Rupl = 0;
                 Gupl = 0;
                 Bupl = 0;
            }
            
            if ( i < height - 1) 
            {
                 Rdown = tmp[i + 1][j].rgbtRed;
                 Gdown = tmp[i + 1][j].rgbtGreen;
                 Bdown = tmp[i + 1][j].rgbtBlue;
            }
            
            else
            {
                 Rdown = 0;
                 Gdown = 0;
                 Bdown = 0;
            }
            
            if (i < height - 1 && j < width - 1)
            {
                 Rdownr = tmp[i + 1][j + 1].rgbtRed;
                 Gdownr = tmp[i + 1][j + 1].rgbtGreen;
                 Bdownr = tmp[i + 1][j + 1].rgbtBlue;
            }
            
            else
            {
                 Rdownr = 0;
                 Gdownr = 0;
                 Bdownr = 0;
            }
            
            if (i < height - 1 && j > 0)
            {
                 Rdownl = tmp[i + 1][j - 1].rgbtRed;
                 Gdownl = tmp[i + 1][j - 1].rgbtGreen;
                 Bdownl = tmp[i + 1][j - 1].rgbtBlue;
            }
            
            else
            {
                 Rdownl = 0;
                 Gdownl = 0;
                 Bdownl = 0;
            }
            
            R = tmp[i][j].rgbtRed;
            G = tmp[i][j].rgbtGreen;
            B = tmp[i][j].rgbtBlue;
            
            Ravg = R + Rleft + Rright + Rup + Rupr + Rupl + Rdown + Rdownl + Rdownr;
            Gavg = G + Gleft + Gright + Gup + Gupr + Gupl + Gdown + Gdownl + Gdownr;
            Bavg = B + Bleft + Bright + Bup + Bupr + Bupl + Bdown + Bdownl + Bdownr;
            
            if (i > 0 && j > 0 && i < height - 1 && j < width - 1)
            {
                     Ravg = round(Ravg / 9);
                     Gavg = round(Gavg / 9);
                     Bavg = round(Bavg / 9);
            }
            
            //top left corner
            
            if ( i == 0 && j == 0)
            {
                Ravg = round(Ravg / 4);
                Bavg = round(Bavg / 4);
                Gavg = round(Gavg / 4);
            }
            
            //top right corner
            if (i == 0 && j == width - 1)
            {
                Ravg = round(Ravg / 4);
                Bavg = round(Bavg / 4);
                Gavg = round(Gavg / 4);
            }
            
            //bottom left corner
            if (i == height - 1 && j == 0)
            {
                Ravg = round(Ravg / 4);
                Bavg = round(Bavg / 4);
                Gavg = round(Gavg / 4);
            }
            //bottom right corner
            if (i == height - 1 && j == width - 1)
            {
                Ravg = round(Ravg / 4);
                Bavg = round(Bavg / 4);
                Gavg = round(Gavg / 4);
            }
            //if not on bottom most and top most layer of pixels
            if (i > 0 && i < height - 1)
            {
                //if on leftmost edge or right most edge - source of mistake?
                if (j == 0 || j == width - 1)
                {
                    Ravg = round(Ravg / 6);
                    Bavg = round(Bavg / 6);
                    Gavg = round(Gavg / 6);
                }
            }
            
            //if not on leftmost or rightmost row of pixels
            if (j > 0 && j < width - 1)
            {
                // if on top or bottom edge
                if ( i == 0 || i == width - 1)
                {
                    Ravg = round(Ravg / 6);
                    Bavg = round(Bavg / 6);
                    Gavg = round(Gavg / 6);
                }
            }
            
            
            image[i][j].rgbtBlue = Bavg;
            image[i][j].rgbtRed = Ravg;
            image[i][j].rgbtGreen = Gavg;

            //if there is a left(if j!= 0), if there is a right (if j!= height or height-1)
            //if there is an up and a left - double condition
        }
    }
    
    
    return;
}
