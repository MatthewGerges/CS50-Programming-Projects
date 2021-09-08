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

            //set the red blue and green channel of the pixels equal to the average of the original values of all the channels
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;

        }
    }
    return;
}

// Convert image to sepia - this filter only works for the less comfortable distribution code!!
void sepia(int height, int width, RGBTRIPLE image[height][width])
{   
    //iterate through every column
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

            //if the sepia formulas exceed values of 255, round them down to 255
            if (sblue > 255)
            {
                sblue = 255;
            }
            if (sred > 255)
            {
                sred = 255;
            }
            if (sgreen > 255)
            {
                sgreen = 255;
            }

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
        for (int j = 0; j < width / 2; j++)
        {
            //we go until the half of width because switching 2 numbers takes 1 step, that is why this iteration is halved
            //Also, if we are successful at switching all the pixels we will stop in the middle
            
            //we subtract 1 from the width because we would be out of the bounds of the array if we didn't (since width starts counting from 1 and the array starts counting from 0)
            
            //tempb, tempr and tempg are temporary variables that hold the values for the red blue and green channels of the current pixel
            //to switch the position of 2 variables, you need 3 (one extra unneeded), just like switching drinks
            int tempb = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            image[i][width - 1 - j].rgbtBlue = tempb;

            //i remains as is because we're switching pixels only on the horizontally opposite sides
            //we switch j with width-1-j because if j is 0 we're switching the pixel at index 0 in the beginning of the row with the one at the very end
            int tempr = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][width - 1 - j].rgbtRed = tempr;

            int tempg = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][width - 1 - j].rgbtGreen = tempg;
        }

    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //We need to create a temporary variable that stores all the pixels (a duplicate of image)
    //to be a duplicate of image- it has to be the same datatype as image
    RGBTRIPLE tmp[height][width];
    
    //copy the pixels in each row and column of image into tmp
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp[i][j] = image[i][j];
        }
    }
    //temp [i][j] = image [i][j]; maybe mistake
    
    //Create and initialize all the variables
    //Doing it in the for loop would be smarter because then you would not need any else statements
    //9 variables each for red blue and green to signify the 9 surrounding pixels including the pixel itself
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
    
    
    float Ravg = 0;
    float Bavg = 0;
    float Gavg = 0;


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < height; j++)
        {
            //if there is a left/ pixel is not on left edge
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
            //if the pixel is not on the rightmost edge
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
            //if not on top edge
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
            //if not on rightmost edge and if not on top most edge
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
            //if not top left corner (leftmost and topmost)
            if (i > 0 && j > 0)
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
            //if not on bottom most edge
            if (i < height - 1) 
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
            //if not on bottom and rightmost- bottom right corner
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
            //if not on bottom left
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
            
            //Smarter + more efficient way to do the above = each if condition has a counter++
            //that way you don't have to check what type of pixel it is to divide by a certain number
            //Instead you could just divide by the counter
            
            //These are the red, green and blue channels of the pixels themselves
            R = tmp[i][j].rgbtRed;
            G = tmp[i][j].rgbtGreen;
            B = tmp[i][j].rgbtBlue;
            
            //the totals of the channels of all the surrounding 9 pixels;
            Ravg = R + Rleft + Rright + Rup + Rupr + Rupl + Rdown + Rdownl + Rdownr;
            Gavg = G + Gleft + Gright + Gup + Gupr + Gupl + Gdown + Gdownl + Gdownr;
            Bavg = B + Bleft + Bright + Bup + Bupr + Bupl + Bdown + Bdownl + Bdownr;
            
            //if the pixel is a middle pixel, then none of the values are 0 so you can divide by 9
            if (i > 0 && j > 0 && i < height - 1 && j < width - 1)
            {
                Ravg = round(Ravg / 9);
                Gavg = round(Gavg / 9);
                Bavg = round(Bavg / 9);
            }
            
            //top left corner
            
            if (i == 0 && j == 0)
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
                //if on leftmost edge or right most edge
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
                if (i == 0 || i == width - 1)
                {
                    Ravg = round(Ravg / 6);
                    Bavg = round(Bavg / 6);
                    Gavg = round(Gavg / 6);
                }
            }
            
            //set the red, blue, and green channels of each pixel to the rounded average of its surronding pixels
            image[i][j].rgbtBlue = Bavg;
            image[i][j].rgbtRed = Ravg;
            image[i][j].rgbtGreen = Gavg;
        }
    }
}



// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //set another temporary variable that will be a copy of the original image (avoid overwriting the original and using the new calculated values to make further calculations instead of basing it off the Original)
    RGBTRIPLE tmp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //the variables representing the red, blue, and green channels of each pixel and its surrounding ones are created and intialized to 0
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
            
            //if not on leftmost edge
            if (j > 0)
            {
                Rleft = tmp[i][j - 1].rgbtRed;
                Gleft = tmp[i][j - 1].rgbtGreen;
                Bleft = tmp[i][j - 1].rgbtBlue;
            }
            //if not on right edge
            if (j < width - 1)
            {
                Rright = tmp[i][j + 1].rgbtRed;
                Gright = tmp[i][j + 1].rgbtGreen;
                Bright = tmp[i][j + 1].rgbtBlue;
            }
            //if not on top
            if (i > 0)
            {
                Rup = tmp[i - 1][j].rgbtRed;
                Gup = tmp[i - 1][j].rgbtGreen;
                Bup = tmp[i - 1][j].rgbtBlue;
            }
            //if there is a pixel to the top right
            if (j < width - 1 && i > 0)
            {
                Rupr = tmp[i - 1][j + 1].rgbtRed;
                Gupr = tmp[i - 1][j + 1].rgbtGreen;
                Bupr = tmp[i - 1][j + 1].rgbtBlue;
            }
            //if there is a pixel to the top left
            if (i > 0 && j > 0)
            {
                Rupl = tmp[i - 1][j - 1].rgbtRed;
                Gupl = tmp[i - 1][j - 1].rgbtGreen;
                Bupl = tmp[i - 1][j - 1].rgbtBlue;
            }
            //if there is a pixel to the bottom
            if (i < height - 1) 
            {
                Rdown = tmp[i + 1][j].rgbtRed;
                Gdown = tmp[i + 1][j].rgbtGreen;
                Bdown = tmp[i + 1][j].rgbtBlue;
            }
            //if there is a pixel on the bottom right
            if (i < height - 1 && j < width - 1)
            {
                Rdownr = tmp[i + 1][j + 1].rgbtRed;
                Gdownr = tmp[i + 1][j + 1].rgbtGreen;
                Bdownr = tmp[i + 1][j + 1].rgbtBlue;
            }
            //if there is a pixel on the bottom left
            if (i < height - 1 && j > 0)
            {
                Rdownl = tmp[i + 1][j - 1].rgbtRed;
                Gdownl = tmp[i + 1][j - 1].rgbtGreen;
                Bdownl = tmp[i + 1][j - 1].rgbtBlue;
            }
            
            //red, blue, and green channel values of the actual pixel (dead center) based on the iteration of the loop
            R = tmp[i][j].rgbtRed;
            G = tmp[i][j].rgbtGreen;
            B = tmp[i][j].rgbtBlue;
            
            //run the r,b,g.t values of the pixel and its surrounding (8) pixels through a convolution matrix in the x-direction 
            //based on the sobel algorith
            int RGx = Rupl * -1 + Rup * 0 + Rupr * 1 + Rleft * -2 + R * 0 + Rright * 2 + Rdownl * -1 + Rdown * 0 + Rdownr * 1;
            int GGx = Gupl * -1 + Gup * 0 + Gupr * 1 + Gleft * -2 + G * 0 + Gright * 2 + Gdownl * -1 + Gdown * 0 + Gdownr * 1;
            int BGx = Bupl * -1 + Bup * 0 + Bupr * 1 + Bleft * -2 + B * 0 + Bright * 2 + Bdownl * -1 + Bdown * 0 + Bdownr * 1;
            
            //run the red, green, and blue values of the pixel and its surroudning (8) pixels through a convolution matrix in the y-direction
            int RGy = Rupl * -1 + Rup * -2 + Rupr * -1 + Rleft * 0 + R * 0 + Rright * 0 + Rdownl * 1 + Rdown * 2 + Rdownr * 1;
            int GGy = Gupl * -1 + Gup * -2 + Gupr * -1 + Gleft * 0 + G * 0 + Gright * 0 + Gdownl * 1 + Gdown * 2 + Gdownr * 1;
            int BGy = Bupl * -1 + Bup * -2 + Bupr * -1 + Bleft * 0 + B * 0 + Bright * 0 + Bdownl * 1 + Bdown * 2 + Bdownr * 1;
            
            //square each the values from each matrix
            int RGx2 = RGx * RGx;
            int GGx2 = GGx * GGx;
            int BGx2 = BGx * BGx;
            
            int RGy2 = RGy * RGy;
            int GGy2 = GGy * GGy;
            int BGy2 = BGy * BGy;
            
            //set the R,G,B channel values of each pixel to the square root of the convolution matrix in the x- direction squared + the one in the y-direction squared
            float Rfinal = round(sqrt(RGx2 + RGy2));
            //if the result of the squareroot is greater than 255, cap it at 255
            if (Rfinal > 255)
            {
                Rfinal = 255;
            }

            float Gfinal = round(sqrt(GGx2 + GGy2));
            if (Gfinal > 255)
            {
                Gfinal = 255;
            }

            float Bfinal = round(sqrt(BGx2 + BGy2));
            if (Bfinal > 255)
            {
                Bfinal = 255;
            }

            //set the red blue and green channels of the pixel equal to the values of the convolution matrixes
            image[i][j].rgbtRed = Rfinal;
            image[i][j].rgbtGreen = Gfinal;
            image[i][j].rgbtBlue = Bfinal;

        }
    }
}
