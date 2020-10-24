#include "helpers.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / (float)3);
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
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j <= width - 1 - j; j++)
        {

            //Red
            int temp = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][width - 1 - j].rgbtRed = temp;

            //Green
            temp = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][width - 1 - j].rgbtGreen = temp;

            //blue
            temp = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            image[i][width - 1 - j].rgbtBlue = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //makes copy of image 2D array by allocating memory to copy
    //Copy is a pointer to an array[width]
    //arrays are pointers so the notation below makes 2D array of RBGTriple
    RGBTRIPLE(*copy)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    //Checks the nine possible cases for regions in an image and averages out each color
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(i == 0 && j == 0)
            {
                image[i][j].rgbtRed = round((copy[i][j+1].rgbtRed + copy[i+1][j].rgbtRed +copy[i+1][j+1].rgbtRed + copy[i][j].rgbtRed)/(float)4);
                image[i][j].rgbtBlue = round((copy[i][j+1].rgbtBlue + copy[i+1][j].rgbtBlue +copy[i+1][j+1].rgbtBlue + copy[i][j].rgbtBlue)/(float)4);
                image[i][j].rgbtGreen = round((copy[i][j+1].rgbtGreen + copy[i+1][j].rgbtGreen +copy[i+1][j+1].rgbtGreen + copy[i][j].rgbtGreen)/(float)4);
            }
            else if(i == 0 && j == width - 1)
            {
                image[i][j].rgbtRed = round((copy[i][j-1].rgbtRed + copy[i+1][j-1].rgbtRed +copy[i+1][j].rgbtRed + copy[i][j].rgbtRed)/(float)4);
                image[i][j].rgbtBlue = round((copy[i][j-1].rgbtBlue + copy[i+1][j-1].rgbtBlue +copy[i+1][j].rgbtBlue + copy[i][j].rgbtBlue)/(float)4);
                image[i][j].rgbtGreen = round((copy[i][j-1].rgbtGreen + copy[i+1][j-1].rgbtGreen +copy[i+1][j].rgbtGreen + copy[i][j].rgbtGreen)/(float)4);
            }
            else if(i == height - 1 && j == 0)
            {
                image[i][j].rgbtRed = round((copy[i-1][j].rgbtRed + copy[i-1][j+1].rgbtRed +copy[i][j+1].rgbtRed + copy[i][j].rgbtRed)/(float)4);
                image[i][j].rgbtBlue = round((copy[i-1][j].rgbtBlue + copy[i-1][j+1].rgbtBlue +copy[i][j+1].rgbtBlue + copy[i][j].rgbtBlue)/(float)4);
                image[i][j].rgbtGreen = round((copy[i-1][j].rgbtGreen + copy[i-1][j+1].rgbtGreen +copy[i][j+1].rgbtGreen + copy[i][j].rgbtGreen)/(float)4);
            }
            else if(i == height - 1 && j == width - 1)
            {
                image[i][j].rgbtRed = round((copy[i-1][j].rgbtRed + copy[i-1][j-1].rgbtRed +copy[i][j-1].rgbtRed + copy[i][j].rgbtRed)/(float)4);
                image[i][j].rgbtBlue = round((copy[i-1][j].rgbtBlue + copy[i-1][j-1].rgbtBlue +copy[i][j-1].rgbtBlue + copy[i][j].rgbtBlue)/(float)4);
                image[i][j].rgbtGreen = round((copy[i-1][j].rgbtGreen + copy[i-1][j-1].rgbtGreen +copy[i][j-1].rgbtGreen + copy[i][j].rgbtGreen)/(float)4);
            }
            else if(i == 0)
            {
                image[i][j].rgbtRed = round((copy[i][j-1].rgbtRed + copy[i+1][j-1].rgbtRed +copy[i+1][j].rgbtRed + copy[i+1][j+1].rgbtRed + copy[i][j+1].rgbtRed + copy[i][j].rgbtRed)/(float)6);
                image[i][j].rgbtBlue = round((copy[i][j-1].rgbtBlue + copy[i+1][j-1].rgbtBlue +copy[i+1][j].rgbtBlue + copy[i+1][j+1].rgbtBlue + copy[i][j+1].rgbtBlue + copy[i][j].rgbtBlue)/(float)6);
                image[i][j].rgbtGreen = round((copy[i][j-1].rgbtGreen + copy[i+1][j-1].rgbtGreen +copy[i+1][j].rgbtGreen + copy[i+1][j+1].rgbtGreen + copy[i][j+1].rgbtGreen + copy[i][j].rgbtGreen)/(float)6);
            }
            else if(j == 0)
            {
                image[i][j].rgbtRed = round((copy[i-1][j].rgbtRed + copy[i-1][j+1].rgbtRed +copy[i][j+1].rgbtRed + copy[i+1][j+1].rgbtRed + copy[i+1][j].rgbtRed + copy[i][j].rgbtRed)/(float)6);
                image[i][j].rgbtBlue = round((copy[i-1][j].rgbtBlue + copy[i-1][j+1].rgbtBlue +copy[i][j+1].rgbtBlue + copy[i+1][j+1].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i][j].rgbtBlue)/(float)6);
                image[i][j].rgbtGreen = round((copy[i-1][j].rgbtGreen + copy[i-1][j+1].rgbtGreen +copy[i][j+1].rgbtGreen + copy[i+1][j+1].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i][j].rgbtGreen)/(float)6);
            }
            else if(j == width - 1)
            {
                image[i][j].rgbtRed = round((copy[i-1][j].rgbtRed + copy[i-1][j-1].rgbtRed +copy[i][j-1].rgbtRed + copy[i+1][j-1].rgbtRed + copy[i+1][j].rgbtRed + copy[i][j].rgbtRed)/(float)6);
                image[i][j].rgbtBlue = round((copy[i-1][j].rgbtBlue + copy[i-1][j-1].rgbtBlue +copy[i][j-1].rgbtBlue + copy[i+1][j-1].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i][j].rgbtBlue)/(float)6);
                image[i][j].rgbtGreen = round((copy[i-1][j].rgbtGreen + copy[i-1][j-1].rgbtGreen +copy[i][j-1].rgbtGreen + copy[i+1][j-1].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i][j].rgbtGreen)/(float)6);
            }
            else if(i == height -1)
            {
                image[i][j].rgbtRed = round((copy[i][j-1].rgbtRed + copy[i-1][j-1].rgbtRed +copy[i-1][j].rgbtRed + copy[i-1][j+1].rgbtRed + copy[i][j+1].rgbtRed + copy[i][j].rgbtRed)/(float)6);
                image[i][j].rgbtBlue = round((copy[i][j-1].rgbtBlue + copy[i-1][j-1].rgbtBlue +copy[i-1][j].rgbtBlue + copy[i-1][j+1].rgbtBlue + copy[i][j+1].rgbtBlue + copy[i][j].rgbtBlue)/(float)6);
                image[i][j].rgbtGreen = round((copy[i][j-1].rgbtGreen + copy[i-1][j-1].rgbtGreen +copy[i-1][j].rgbtGreen + copy[i-1][j+1].rgbtGreen + copy[i][j+1].rgbtGreen + copy[i][j].rgbtGreen)/(float)6);
            }
            else
            {
                image[i][j].rgbtRed = round((copy[i-1][j-1].rgbtRed + copy[i-1][j].rgbtRed +copy[i-1][j+1].rgbtRed + copy[i][j-1].rgbtRed + copy[i][j+1].rgbtRed
                    + copy[i+1][j-1].rgbtRed + copy[i+1][j].rgbtRed + copy[i+1][j+1].rgbtRed + copy[i][j].rgbtRed)/(float)9);
                image[i][j].rgbtBlue = round((copy[i-1][j-1].rgbtBlue + copy[i-1][j].rgbtBlue +copy[i-1][j+1].rgbtBlue + copy[i][j-1].rgbtBlue + copy[i][j+1].rgbtBlue
                    + copy[i+1][j-1].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i+1][j+1].rgbtBlue + copy[i][j].rgbtBlue)/(float)9);
                image[i][j].rgbtGreen = round((copy[i-1][j-1].rgbtGreen + copy[i-1][j].rgbtGreen +copy[i-1][j+1].rgbtGreen + copy[i][j-1].rgbtGreen + copy[i][j+1].rgbtGreen
                    + copy[i+1][j-1].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i+1][j+1].rgbtGreen + copy[i][j].rgbtGreen)/(float)9);
            }
        }
    }
    free(copy);
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //Creates copy of image
    RGBTRIPLE(*copy)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    //Gx Matrix
    //     {-1, 0, 1},
    //     {-2, 0, 2},
    //     {-1, 0, 1}

    //Gy Matrix
    //     {-1, -2, -1},
    //     { 0,  0,  0},
    //     { 1,  2,  1}


    float gX, gY;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {

            if(i == 0 && j == 0)
            {
                //intializing red channel
                gX = copy[i][j+1].rgbtRed * (float)2.0 + copy[i+1][j+1].rgbtRed;
                gY = copy[i+1][j].rgbtRed * (float)2.0 +copy[i+1][j+1].rgbtRed;
                if(sqrt(pow(gX,2) + pow(gY,2)) > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else{
                    image[i][j].rgbtRed = round(sqrt(pow(gX,2) + pow(gY,2)));
                }

                //initializing green channel
                gX = copy[i][j+1].rgbtGreen * (float)2.0 + copy[i+1][j+1].rgbtGreen;
                gY = copy[i+1][j].rgbtGreen * (float)2.0 +copy[i+1][j+1].rgbtGreen;
                if(sqrt(pow(gX,2) + pow(gY,2)) > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else{
                    image[i][j].rgbtGreen = round(sqrt(pow(gX,2) + pow(gY,2)));
                }

                //initializing blue channel
                gX = copy[i][j+1].rgbtBlue * (float)2.0 + copy[i+1][j+1].rgbtBlue;
                gY = copy[i+1][j].rgbtBlue * (float)2.0 +copy[i+1][j+1].rgbtBlue;
                if(sqrt(pow(gX,2) + pow(gY,2)) > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else{
                    image[i][j].rgbtBlue = round(sqrt(pow(gX,2) + pow(gY,2)));
                }
            }
            else if(i == 0 && j == width - 1)
            {
               //intializing red channel
                gX = copy[i][j-1].rgbtRed * (float)-2.0 + copy[i+1][j-1].rgbtRed * -1;
                gY = copy[i+1][j].rgbtRed * (float)2.0 +copy[i+1][j-1].rgbtRed;
                if(sqrt(pow(gX,2) + pow(gY,2)) > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else{
                    image[i][j].rgbtRed = round(sqrt(pow(gX,2) + pow(gY,2)));
                }

                //initializing green channel
                gX = copy[i][j-1].rgbtGreen * (float)-2.0 + copy[i+1][j-1].rgbtGreen * -1;
                gY = copy[i+1][j].rgbtGreen * (float)2.0 +copy[i+1][j-1].rgbtGreen;
                if(sqrt(pow(gX,2) + pow(gY,2)) > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else{
                    image[i][j].rgbtGreen = round(sqrt(pow(gX,2) + pow(gY,2)));
                }

                //initializing blue channel
                gX = copy[i][j-1].rgbtBlue * (float)-2.0 + copy[i+1][j-1].rgbtBlue * -1;
                gY = copy[i+1][j].rgbtBlue * (float)2.0 +copy[i+1][j-1].rgbtBlue;
                if(sqrt(pow(gX,2) + pow(gY,2)) > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else{
                    image[i][j].rgbtBlue = round(sqrt(pow(gX,2) + pow(gY,2)));
                }
            }
            else if(i == height - 1 && j == 0)
            {
                //initializing red channel
                gX = copy[i][j+1].rgbtRed * (float)2.0 + copy[i-1][j+1].rgbtRed;
                gY = copy[i-1][j].rgbtRed * (float)-2.0 +copy[i-1][j+1].rgbtRed * -1;
                if(sqrt(pow(gX,2) + pow(gY,2)) > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else{
                    image[i][j].rgbtRed = round(sqrt(pow(gX,2) + pow(gY,2)));
                }

                //initializing green channel
                gX = copy[i][j+1].rgbtGreen * (float)2.0 + copy[i-1][j+1].rgbtGreen;
                gY = copy[i-1][j].rgbtGreen * (float)-2.0 +copy[i-1][j+1].rgbtGreen * -1;
                if(sqrt(pow(gX,2) + pow(gY,2)) > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else{
                    image[i][j].rgbtGreen = round(sqrt(pow(gX,2) + pow(gY,2)));
                }

                //initializing blue channel
                gX = copy[i][j+1].rgbtBlue * (float)2.0 + copy[i-1][j+1].rgbtBlue;
                gY = copy[i-1][j].rgbtBlue * (float)-2.0 +copy[i-1][j+1].rgbtBlue * -1;
                if(sqrt(pow(gX,2) + pow(gY,2)) > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else{
                    image[i][j].rgbtBlue = round(sqrt(pow(gX,2) + pow(gY,2)));
                }
            }
            else if(i == height - 1 && j == width - 1)
            {
               //initializing red channel
                gX = copy[i][j-1].rgbtRed * (float)-2.0 + copy[i-1][j-1].rgbtRed * -1;
                gY = copy[i-1][j].rgbtRed * (float)-2.0 +copy[i-1][j-1].rgbtRed * -1;
                if(sqrt(pow(gX,2) + pow(gY,2)) > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else{
                    image[i][j].rgbtRed = round(sqrt(pow(gX,2) + pow(gY,2)));
                }

                //initializing blue channel
                gX = copy[i][j-1].rgbtGreen * (float)-2.0 + copy[i-1][j-1].rgbtGreen * -1;
                gY = copy[i-1][j].rgbtGreen * (float)-2.0 +copy[i-1][j-1].rgbtGreen * -1;
                if(sqrt(pow(gX,2) + pow(gY,2)) > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else{
                    image[i][j].rgbtGreen = round(sqrt(pow(gX,2) + pow(gY,2)));
                }

                //initializing green channel
                gX = copy[i][j-1].rgbtBlue * (float)-2.0 + copy[i-1][j-1].rgbtBlue * -1;
                gY = copy[i-1][j].rgbtBlue * (float)-2.0 +copy[i-1][j-1].rgbtBlue * -1;
                if(sqrt(pow(gX,2) + pow(gY,2)) > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else{
                    image[i][j].rgbtBlue = round(sqrt(pow(gX,2) + pow(gY,2)));
                }

            }
            else if(i == 0)
            {
                //initializing red channel
                gX = copy[i][j-1].rgbtRed * (float)-2.0 + copy[i+1][j-1].rgbtRed * -1 + copy[i+1][j+1].rgbtRed + copy[i][j+1].rgbtRed * 2;
                gY = copy[i+1][j-1].rgbtRed + copy[i+1][j].rgbtRed * (float)2.0 + copy[i+1][j+1].rgbtRed;
                if(sqrt(pow(gX,2) + pow(gY,2)) > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else{
                    image[i][j].rgbtRed = round(sqrt(pow(gX,2) + pow(gY,2)));
                }

                //initializing green channel
                gX = copy[i][j-1].rgbtGreen * (float)-2.0 + copy[i+1][j-1].rgbtGreen * -1 + copy[i+1][j+1].rgbtGreen + copy[i][j+1].rgbtGreen * 2;
                gY = copy[i+1][j-1].rgbtGreen + copy[i+1][j].rgbtGreen * (float)2.0 + copy[i+1][j+1].rgbtGreen;
                if(sqrt(pow(gX,2) + pow(gY,2)) > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else{
                    image[i][j].rgbtGreen = round(sqrt(pow(gX,2) + pow(gY,2)));
                }

                //initializing blue channel
                gX = copy[i][j-1].rgbtBlue * (float)-2.0 + copy[i+1][j-1].rgbtBlue * -1 + copy[i+1][j+1].rgbtBlue + copy[i][j+1].rgbtBlue * 2;
                gY = copy[i+1][j-1].rgbtBlue + copy[i+1][j].rgbtBlue * (float)2.0 + copy[i+1][j+1].rgbtBlue;
                if(sqrt(pow(gX,2) + pow(gY,2)) > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else{
                    image[i][j].rgbtBlue = round(sqrt(pow(gX,2) + pow(gY,2)));
                }
            }
            else if(j == 0)
            {
                //initializing red channel
                gX = copy[i-1][j+1].rgbtRed + copy[i][j+1].rgbtRed * (float)2.0 + copy[i+1][j+1].rgbtRed;
                gY = copy[i-1][j].rgbtRed * (float)-2.0 + copy[i-1][j+1].rgbtRed * -1 + copy[i+1][j+1].rgbtRed + copy[i+1][j].rgbtRed * 2;
                if(sqrt(pow(gX,2) + pow(gY,2)) > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else{
                    image[i][j].rgbtRed = round(sqrt(pow(gX,2) + pow(gY,2)));
                }

                //initializing green channel
                gX = copy[i-1][j+1].rgbtGreen + copy[i][j+1].rgbtGreen * (float)2.0 + copy[i+1][j+1].rgbtGreen;
                gY = copy[i-1][j].rgbtGreen * (float)-2.0 + copy[i-1][j+1].rgbtGreen * -1 + copy[i+1][j+1].rgbtGreen + copy[i+1][j].rgbtGreen * 2;
                if(sqrt(pow(gX,2) + pow(gY,2)) > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else{
                    image[i][j].rgbtGreen = round(sqrt(pow(gX,2) + pow(gY,2)));
                }

                //initializing blue channel
                gX = copy[i-1][j+1].rgbtBlue + copy[i][j+1].rgbtBlue * (float)2.0 + copy[i+1][j+1].rgbtBlue;
                gY = copy[i-1][j].rgbtBlue * (float)-2.0 + copy[i-1][j+1].rgbtBlue * -1 + copy[i+1][j+1].rgbtBlue + copy[i+1][j].rgbtBlue * 2;
                if(sqrt(pow(gX,2) + pow(gY,2)) > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else{
                    image[i][j].rgbtBlue = round(sqrt(pow(gX,2) + pow(gY,2)));
                }

            }
            else if(j == width - 1)
            {
                //initializing red channel
                gX = copy[i-1][j-1].rgbtRed * -1 + copy[i][j-1].rgbtRed * (float)-2.0 + copy[i+1][j-1].rgbtRed * -1;
                gY = copy[i-1][j].rgbtRed * (float)-2.0 + copy[i-1][j-1].rgbtRed * -1 + copy[i+1][j-1].rgbtRed + copy[i+1][j].rgbtRed * 2.0;
                if(sqrt(pow(gX,2) + pow(gY,2)) > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else{
                    image[i][j].rgbtRed = round(sqrt(pow(gX,2) + pow(gY,2)));
                }

                 //initializing green channel
                gX = copy[i-1][j-1].rgbtGreen * -1 + copy[i][j-1].rgbtGreen * (float)-2.0 + copy[i+1][j-1].rgbtGreen * -1;
                gY = copy[i-1][j].rgbtGreen * (float)-2.0 + copy[i-1][j-1].rgbtGreen * -1 + copy[i+1][j-1].rgbtGreen + copy[i+1][j].rgbtGreen * 2.0;
                if(sqrt(pow(gX,2) + pow(gY,2)) > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else{
                    image[i][j].rgbtGreen = round(sqrt(pow(gX,2) + pow(gY,2)));
                }

                 //initializing blue channel
                gX = copy[i-1][j-1].rgbtBlue * -1 + copy[i][j-1].rgbtBlue * (float)-2.0 + copy[i+1][j-1].rgbtBlue * -1;
                gY = copy[i-1][j].rgbtBlue * (float)-2.0 + copy[i-1][j-1].rgbtBlue * -1 + copy[i+1][j-1].rgbtBlue + copy[i+1][j].rgbtBlue * 2.0;
                if(sqrt(pow(gX,2) + pow(gY,2)) > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else{
                    image[i][j].rgbtBlue = round(sqrt(pow(gX,2) + pow(gY,2)));;
                }

            }
            else if(i == height - 1)
            {
                 //initializing red channel
                gX = copy[i][j-1].rgbtRed * (float)-2.0 + copy[i-1][j-1].rgbtRed * -1 + copy[i-1][j+1].rgbtRed + copy[i][j+1].rgbtRed * 2;
                gY = copy[i-1][j-1].rgbtRed * -1 + copy[i-1][j].rgbtRed * (float)-2.0 + copy[i-1][j+1].rgbtRed * -1;
                if(sqrt(pow(gX,2) + pow(gY,2)) > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else{
                    image[i][j].rgbtRed = round(sqrt(pow(gX,2) + pow(gY,2)));
                }

                 //initializing green channel
                gX = copy[i][j-1].rgbtGreen * (float)-2.0 + copy[i-1][j-1].rgbtGreen * -1 + copy[i-1][j+1].rgbtGreen + copy[i][j+1].rgbtGreen * 2;
                gY = copy[i-1][j-1].rgbtGreen * -1 + copy[i-1][j].rgbtGreen * (float)-2.0 + copy[i-1][j+1].rgbtGreen * -1;
                if(sqrt(pow(gX,2) + pow(gY,2)) > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else{
                    image[i][j].rgbtGreen = round(sqrt(pow(gX,2) + pow(gY,2)));
                }

                 //initializing blue channel
                gX = copy[i][j-1].rgbtBlue * (float)-2.0 + copy[i-1][j-1].rgbtBlue * -1 + copy[i-1][j+1].rgbtBlue + copy[i][j+1].rgbtBlue * 2;
                gY = copy[i-1][j-1].rgbtBlue * -1 + copy[i-1][j].rgbtBlue * (float)-2.0 + copy[i-1][j+1].rgbtBlue * -1;
                if(sqrt(pow(gX,2) + pow(gY,2)) > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else{
                    image[i][j].rgbtBlue = round(sqrt(pow(gX,2) + pow(gY,2)));
                }
            }
            else
            {
                 //initializing red channel
                gX = copy[i-1][j-1].rgbtRed * -1 + copy[i][j-1].rgbtRed * (float)-2.0 + copy[i+1][j-1].rgbtRed * -1 + copy[i-1][j+1].rgbtRed + copy[i][j+1].rgbtRed * 2 + copy[i+1][j+1].rgbtRed;
                gY = copy[i-1][j-1].rgbtRed * -1 + copy[i-1][j].rgbtRed * (float)-2.0 + copy[i-1][j+1].rgbtRed * -1 + copy[i+1][j-1].rgbtRed + copy[i+1][j].rgbtRed * 2 + copy[i+1][j+1].rgbtRed;
                if(sqrt(pow(gX,2) + pow(gY,2)) > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else{
                    image[i][j].rgbtRed = round(sqrt(pow(gX,2) + pow(gY,2)));
                }

                 //initializing green channel
                gX = copy[i-1][j-1].rgbtGreen * -1 + copy[i][j-1].rgbtGreen * (float)-2.0 + copy[i+1][j-1].rgbtGreen * -1 + copy[i-1][j+1].rgbtGreen + copy[i][j+1].rgbtGreen * 2 + copy[i+1][j+1].rgbtGreen;
                gY = copy[i-1][j-1].rgbtGreen * -1 + copy[i-1][j].rgbtGreen * (float)-2.0 + copy[i-1][j+1].rgbtGreen * -1 + copy[i+1][j-1].rgbtGreen + copy[i+1][j].rgbtGreen * 2 + copy[i+1][j+1].rgbtGreen;
                if(sqrt(pow(gX,2) + pow(gY,2)) > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else{
                    image[i][j].rgbtGreen = round(sqrt(pow(gX,2) + pow(gY,2)));
                }

                 //initializing blue channel
                gX = copy[i-1][j-1].rgbtBlue * -1 + copy[i][j-1].rgbtBlue * (float)-2.0 + copy[i+1][j-1].rgbtBlue * -1 + copy[i-1][j+1].rgbtBlue + copy[i][j+1].rgbtBlue * 2 
                    + copy[i+1][j+1].rgbtBlue;
                gY = copy[i-1][j-1].rgbtBlue * -1 + copy[i-1][j].rgbtBlue * (float)-2.0 + copy[i-1][j+1].rgbtBlue * -1 + copy[i+1][j-1].rgbtBlue + copy[i+1][j].rgbtBlue * 2 
                    + copy[i+1][j+1].rgbtBlue;
                if(sqrt(pow(gX,2) + pow(gY,2)) > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else
                {
                    image[i][j].rgbtBlue = round(sqrt(pow(gX, 2) + pow(gY, 2)));
                }
            }

        }
    }

    free(copy);
    return;
}
