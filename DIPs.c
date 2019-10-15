#include "DIPs.h"
#include "Image.h"

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>
/* Example of DIP */
/* make the picture color black & white */
IMAGE *BlackNWhite(IMAGE *image)
{
    
    int x, y, tmp;
    int newR, newG, newB;
    
    assert(image);

    for (y = 0; y < ImageHeight(image); y++)
    {
        for (x = 0; x < ImageWidth(image); x++)
        {
		newR = GetPixelR(image, x, y);
		newG = GetPixelG(image, x, y);
		newB = GetPixelB(image, x, y);
		
		tmp = (newR + newG + newB)/3;

		SetPixelR(image, x, y, tmp);
		SetPixelG(image, x, y, tmp);
		SetPixelB(image, x, y, tmp);           
        }
    }
  return image;
}

/* Add edge to the image*/
IMAGE *Edge(IMAGE *image) 
{
    assert(image);

    IMAGE* Temp_Image = NULL;
 
    int             x, y, m, n, a, b;
 
    Temp_Image = CreateImage(ImageWidth(image), ImageHeight(image));

    for (y = 0; y < ImageHeight(image); y++)
    {
        for (x = 0; x < ImageWidth(image); x++) 
	{
            SetPixelR(Temp_Image, x, y, GetPixelR(image, x, y));
            SetPixelG(Temp_Image, x, y, GetPixelG(image, x, y));
            SetPixelB(Temp_Image, x, y, GetPixelB(image, x, y));
        }
    }
    
    int sumR = 0;   // sum of the intensity differences with neighbors 
    int sumG = 0;
    int sumB = 0;

    for (y = 1; y < ImageHeight(image) - 1; y++)
    {
        for (x = 1; x < ImageWidth(image) - 1; x++)
	{
            for (n = -1; n <= 1; n++)
	    {
		for (m = -1; m <= 1; m++) 
		{
                    a = (x + m >= ImageWidth(image)) ? (ImageWidth(image) - 1) : (x + m < 0) ? 0 : x + m;
                    b = (y + n >= ImageHeight(image)) ? (ImageHeight(image) - 1) : (y + n < 0) ? 0 : y + n;
                    sumR += ((GetPixelR(Temp_Image, x, y)) - (GetPixelR(Temp_Image, a, b)));
                    sumG += ((GetPixelG(Temp_Image, x, y)) - (GetPixelG(Temp_Image, a, b)));
                    sumB += ((GetPixelB(Temp_Image, x, y)) - (GetPixelB(Temp_Image, a, b)));
                }
            }
            SetPixelR(image, x, y, (sumR > MAX_PIXEL) ? MAX_PIXEL: (sumR < 0) ? 0: sumR);
            SetPixelG(image, x, y, (sumG > MAX_PIXEL) ? MAX_PIXEL: (sumG < 0) ? 0: sumG);
            SetPixelB(image, x, y, (sumB > MAX_PIXEL) ? MAX_PIXEL: (sumB < 0) ? 0: sumB);
            sumR = sumG = sumB = 0;
        }
    }
//     set all four borders to 0 
    for (y = 0; y < ImageHeight(image); y++) {
        SetPixelR(Temp_Image, 0, y, 0);
        SetPixelG(Temp_Image, 0, y, 0);
        SetPixelB(Temp_Image, 0, y, 0);
        SetPixelR(Temp_Image, ((ImageWidth(image)) - 1), y, 0);
        SetPixelG(Temp_Image, ((ImageWidth(image)) - 1), y, 0);
	SetPixelB(Temp_Image, ((ImageWidth(image)) - 1), y, 0);
    }
    for (x = 0; x < ImageWidth(image); x++) {
        SetPixelR(Temp_Image, x, 0, 0);
        SetPixelG(Temp_Image, x, 0, 0);
        SetPixelB(Temp_Image, x, 0, 0);
        SetPixelR(Temp_Image, x, ((ImageHeight(image)) - 1), 0);
        SetPixelG(Temp_Image, x, ((ImageHeight(image)) - 1), 0);
        SetPixelB(Temp_Image, x, ((ImageHeight(image)) - 1), 0);
    }

	DeleteImage(Temp_Image);
	Temp_Image = NULL;
        	
	return image;
}

// Shuffle the image 
IMAGE *Shuffle(IMAGE *image)
{
    assert(image);

    int block_cnt = SHUFF_HEIGHT_DIV * SHUFF_WIDTH_DIV;
    int block_width = ImageWidth(image)/SHUFF_WIDTH_DIV;
    int block_height = ImageHeight(image)/SHUFF_HEIGHT_DIV;
    int block[SHUFF_WIDTH_DIV][SHUFF_HEIGHT_DIV];
    int i, j;


    srand(time(NULL));
//  Initialize block markers to not done (-1) 
    for (i = 0; i < SHUFF_WIDTH_DIV; i++) {
        for (j = 0; j< SHUFF_HEIGHT_DIV; j++) {
            block[i][j] = -1;
        }
    }

    while (block_cnt > 0) {
        // Generate a random pair of blocks 
        int dest_height = rand() % SHUFF_HEIGHT_DIV;
        int dest_width = rand() % SHUFF_WIDTH_DIV;
        int src_height = rand() % SHUFF_HEIGHT_DIV;
        int src_width = rand() % SHUFF_WIDTH_DIV;

        // Check if these blocks are already swaped, if not swap blocks 
        if ((block[dest_width][dest_height] == -1) && (block[src_width][src_height] == -1)) {
            // Swap blocks 
            for (i = 0; i < block_height; i++) {
                // Init src and dest height offset 
                int h_dest = ((dest_height * block_height) + i) % ImageHeight(image);
                int h_src  = ((src_height * block_height) + i) % ImageWidth(image);
                for (j = 0; j < block_width; j++) {
                    int temp;
                    // Init src and dest width offset 
                    int w_src  = ((src_width * block_width) + j) % ImageWidth(image);
                    int w_dest = ((dest_width * block_width) + j) % ImageWidth(image);

                    temp = GetPixelR(image, w_dest, h_dest);
                    SetPixelR(image, w_dest, h_dest, (GetPixelR(image, w_src, h_src)));
                    SetPixelR(image, w_src, h_src, temp);

                    temp = GetPixelG(image, w_dest, h_dest);
                    SetPixelG(image, w_dest, h_dest, (GetPixelG(image, w_src, h_src)));
                    SetPixelG(image, w_src, h_src, temp);

                    temp = GetPixelB(image, w_dest, h_dest);
                    SetPixelB(image, w_dest, h_dest, (GetPixelB(image, w_src, h_src)));
                    SetPixelB(image, w_src, h_src, temp);
                }
            }
 //            Set marker as done 
            block[dest_width][dest_height] = 1;
            block[src_width][src_height] = 1;
            // Decrease block count 
            block_cnt -= 2; 
// Two blocks are swapped 
        }

    }
	return image;
}

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
