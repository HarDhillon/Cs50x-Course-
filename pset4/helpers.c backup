#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // this nested loop will run through every RGBTRIPLE in the entire picture. e.g [ RGB, RGB, RBG, RBG...] we are looking at 1 RGB each
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Keep it as a float intitally because we dont want to destroy decimial places. later we can int it.
            float favg = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.00;
            // now we can int it. So avg becomes rounded. (dont forget <math.h>)
            int iavg = round(favg);

            image[i][j].rgbtBlue = iavg;
            image[i][j].rgbtGreen = iavg;
            image[i][j].rgbtRed = iavg;
        }
    }
    //function returns void so no need to return any value. Arrays are essentially pointers so when passed into this function the actually array itself (or rather
    // the location to the array) is passed into the function. Therefore changing the actuall array (not a copy of the array). >>Arrays are passed by reference<<
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            //previously tried to leave sepia red as a float, then round it. But results were being rounded 1 off. Above workound works


            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{


    for (int i = 0; i < height; i++)
    {
        // does not work without /2 as you just end up swapping once, then swapping again past half way.
        for (int j = 0; j < width / 2; j++)
        {
            // you need to minus 1 from the width as well because say width is 6, array wil be 0,1,2,3,4,5,. so width( which is 6) MINUS j(0) is 6. but array[6] doesnt exist
            // as array[0] = 0, array[1] = 1, array[2] = 2, array[3] = 3, array[4] = 4, array[5] = 5, so array[6] does not exist
            int tempB = image[i][width - j - 1].rgbtBlue;
            int tempG = image[i][width - j - 1].rgbtGreen;
            int tempR = image[i][width - j - 1].rgbtRed;

            //swap by putting end pixel into a temp array, putting the end triplet into original, then putting original (now in temp) into end triplet
            image[i][width - j - 1].rgbtBlue = image[i][j].rgbtBlue;
            image[i][width - j - 1].rgbtGreen = image[i][j].rgbtGreen;
            image[i][width - j - 1].rgbtRed = image[i][j].rgbtRed;

            //now put temp into original
            image[i][j].rgbtBlue = tempB;
            image[i][j].rgbtGreen = tempG;
            image[i][j].rgbtRed = tempR;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE graph[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Previously this was outside for loop, therefore not resetting it back to 0 to compute average of different grids.
            //numbers are slightly off if count is not a float as you are dividing by integer which does something in c maths?
            float count = 0.0;
            int totalB = 0;
            int totalG = 0;
            int totalR = 0;

            //creating a 3x3 grid in our pixels to blur
            for (int h = -1; h <= 1; h++)
            {
                for (int w = -1; w <= 1; w++)
                {
                    // we dont want to try and grab things OUTSIDE of the grid as the program will fail.
                    //e.g if i is 0, we are at first square in grid, so i + h(which is -1) will try to grab a square that does not exist.
                    //the same goes for j (the width), so agin if j is 0, the square -1 of that (to the left) does not exist and program will crash

                    if (i + h < 0 || i + h > height - 1 || j + w < 0 || j + w > width - 1)
                    {
                        continue;
                    }
                    //if the square is surrounded, e.g not a corner piece we want to total so that we can get the average.
                    totalB += image[i + h][j + w].rgbtBlue;
                    totalG += image[i + h][j + w].rgbtGreen;
                    totalR += image[i + h][j + w].rgbtRed;

                    count += 1;

                }
                //create a temporary graph of what the averages will be in each square
                //again as above issue with slight rounding error, easier to round directly as inputting
                graph[i][j].rgbtBlue = round(totalB / count);
                graph[i][j].rgbtGreen = round(totalG / count);
                graph[i][j].rgbtRed = round(totalR / count);

            }
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //now we need to put the averages back into the original
            image[i][j].rgbtBlue = graph[i][j].rgbtBlue;
            image[i][j].rgbtGreen = graph[i][j].rgbtGreen;
            image[i][j].rgbtRed = graph[i][j].rgbtRed;
        }
    }

    return;
}
