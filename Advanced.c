#include "Advanced.h"
#include "Image.h"
#include "Constants.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>


// Adjust the brightness of an image 
IMAGE *Brightness(IMAGE *image, int brightness) {
	assert(image);
	int tmpR, tmpG, tmpB;
	for (int x=0; x < ImageWidth(image); x++){
		for (int y=0; y < ImageHeight(image); y++){
			
			tmpR = GetPixelR(image, x, y);
			tmpG = GetPixelG(image, x, y);
			tmpB = GetPixelB(image, x, y);			
	
			if (((tmpR) + brightness) > 255){
				SetPixelR(image, x, y, 255);
			}else if(((tmpR) + brightness) < 0){
				SetPixelR(image, x, y, 0);
			}else{
				SetPixelR(image, x, y, (tmpR+brightness));
			}

			if (((tmpG)+ brightness) > 255){
				 SetPixelG(image, x, y, 255);
			}else if(((tmpG)+ brightness) < 0){
				SetPixelG(image, x, y, 0);
			}else{
				SetPixelG(image, x, y, (tmpG+brightness));
			}

			if (((tmpB)+ brightness) > 255){
				SetPixelB(image, x, y, 255);
			}else if(((tmpB)+ brightness) < 0){
				SetPixelB(image, x, y, 0);
			}else{
				SetPixelB(image, x, y, (tmpB+brightness));
			}
		}
	}
	return image;
}

// Mirror an image horizontally 
IMAGE *HMirror(IMAGE *image) 
{
	assert(image);
	int x, y;
	int tmpR, tmpG, tmpB;
	for (y = 0; y < (ImageHeight(image)); y++) 
	{
		for (x = 0; x < (ImageWidth(image) / 2); x++) 
		{
			tmpR = GetPixelR(image, x, y);
			tmpG = GetPixelG(image, x, y);
			tmpB = GetPixelB(image, x ,y);
		
			SetPixelR(image, (ImageWidth(image)-1)-x, y, tmpR);
			SetPixelG(image, (ImageWidth(image)-1)-x, y, tmpG);
			SetPixelB(image, (ImageWidth(image)-1)-x, y, tmpB);
		}
	}
	return image;
}

IMAGE *Resize(IMAGE *image, int percentage)
{
	assert(image);
	int i, j, x, y, xnew, ynew, xnew1, ynew1, state;
	int tmpR, tmpG, tmpB;
	int num, avgR, avgG, avgB;
	int Widthnew = ImageWidth(image) * (percentage/100.00);
	int Heightnew = ImageHeight(image) * (percentage/100.00);	
	
	
	IMAGE *Temp_Image = NULL;
	Temp_Image = CreateImage(Widthnew, Heightnew);
	assert(Temp_Image);
		
	if(percentage == 100)
	{
		state = 1;
	}
	else if(percentage < 100)
	{
		state = 2;	
	}
	else if(percentage > 100)
	{
		state = 3;
	} 
	
	switch(state)
	{
		case 1:	
			printf("You selected a percentage = 100\n");
			DeleteImage(Temp_Image);
			return image;
			break;
	
		case 2:
			printf("You selected a percentage < 100\n");
		
			avgR = 0;
			avgG = 0;	
			avgB = 0;
			num = 0;
			tmpR = 0;
			tmpG = 0;
			tmpB = 0;	
			for(y = 0; y < Heightnew; y++)
			{
				for(x = 0; x < Widthnew; x++)
				{
					xnew = (x / (percentage/100.00));
					ynew = (y / (percentage/100.00));
					xnew1 = ((x + 1)/(percentage/100.00));
					ynew1 = ((y + 1)/(percentage/100.00));
					tmpR = tmpG = tmpB = 0;
					for(i = xnew; i < xnew1; i++)
					{
						for(j = ynew; j < ynew1; j++)
						{
							tmpR += GetPixelR(image, i, j);
							tmpG += GetPixelG(image, i, j);
							tmpB += GetPixelB(image, i, j);
							num++;		
						}//for J
					}//for I
					avgR = tmpR/num;
					avgG = tmpG/num;
					avgB = tmpB/num;
			
					SetPixelR(Temp_Image, x, y, avgR);
					SetPixelG(Temp_Image, x, y, avgG);
					SetPixelB(Temp_Image, x, y, avgB);
					tmpR = tmpG = tmpB = 0;
					num = 0;
				}//for X
			}//for Y
			DeleteImage(image);
			break;
		
		case 3:
			printf("You selected a percentage > 100\n");
	
                        for(y = 0; y < Heightnew; y++)
                        {
                                for(x = 0; x < Widthnew; x++)
                                {
                                        xnew = (x * (100.0/percentage));
                                        ynew = (y * (100.0/percentage));
                                        
					tmpR = GetPixelR(image, xnew, ynew);
					tmpG = GetPixelG(image, xnew, ynew);
					tmpB = GetPixelB(image, xnew, ynew);
	
				        SetPixelR(Temp_Image, x, y, tmpR);
					SetPixelG(Temp_Image, x, y, tmpG);
					SetPixelB(Temp_Image, x, y, tmpB);		
                                }
                        }
			DeleteImage(image);		
			break;
	}
	return Temp_Image;	
}

IMAGE *Saturate(IMAGE *image, float percent)
{
	assert(image);
	float tmpR, tmpG, tmpB;
	float Rt, Gt, Bt; 
	int x, y;
	for(x = 0; x < ImageWidth(image); x++)
	{
		for(y = 0; y < ImageHeight(image); y++ )
		{	
			/*Get Greyscale*/
			Rt = (GetPixelR(image, x, y) + GetPixelG(image, x, y) + GetPixelB(image, x, y)) / 3;
			Gt = Rt;
			Bt = Rt;

			/*Find difference from original*/
			Rt = GetPixelR(image, x, y) - Rt;
			Gt = GetPixelG(image, x, y) - Gt;
			Bt = GetPixelB(image, x, y) - Bt;
	
			/*Add the difference multiplied by percentage*/
			tmpR =  (GetPixelR(image, x, y) + (percent * Rt)/100.00);
			tmpG =  (GetPixelG(image, x, y) + (percent * Gt)/100.00);
			tmpB =  (GetPixelB(image, x, y) + (percent * Bt)/100.00);
			
			if(tmpR < 0)
			{
				tmpR = 0;
			}
			if(tmpR > 255)
			{
				tmpR = 255;
			}
			if(tmpG < 0)
                        {
                                tmpG = 0;
                        }
                        if(tmpG > 255)
                        {
                                tmpG = 255;
                        }
			if(tmpB < 0)
                        {
                                tmpB = 0;
                        }
                        if(tmpB > 255)
                        {
                                tmpB = 255;
                        }
			SetPixelR(image, x, y, tmpR);
			SetPixelG(image, x, y, tmpG);
			SetPixelB(image, x, y, tmpB);
		
		}
	}
	return image;
}

IMAGE *Rotate(IMAGE *image, int option)
{
	
	int state;
	int x, y;
	int tmpR, tmpG, tmpB;
	
	IMAGE *Temp_Image = NULL;
	Temp_Image = CreateImage(ImageHeight(image), ImageWidth(image));
	
	if(option == 1)
        {
                state = 1;
        }
        else if(option == 2)
        {
                state = 2;
        }
        else if(option == 3)
        {
                state = 3;
        }
	else if(option == 4)
	{
		state = 4;
	}	
	
	switch(state)
	{
		case 1: 
			printf("Horizontal Flip Selected\n");
			for(y = 0; y < ImageHeight(image); y++)
			{
				for(x = 0; x < (ImageWidth(image) / 2); x++)
				{
					tmpR = GetPixelR(image, (ImageWidth(image) - 1) - x, y);
					tmpG = GetPixelG(image, (ImageWidth(image) - 1) - x, y);
					tmpB = GetPixelB(image, (ImageWidth(image) - 1) - x, y);
					
					SetPixelR(image, (ImageWidth(image) - 1) - x, y, GetPixelR(image, x, y));
					SetPixelG(image, (ImageWidth(image) - 1) - x, y, GetPixelG(image, x, y));
					SetPixelB(image, (ImageWidth(image) - 1) - x, y, GetPixelB(image, x, y));
		
					SetPixelR(image, x, y, tmpR);
					SetPixelG(image, x, y, tmpG);
					SetPixelB(image, x, y, tmpB);
				}//for x
			}//for
			DeleteImage(Temp_Image);
			return image;
			break;
	
		case 2:
			printf("Vertical Flip Selected\n");
			for(y = 0; y < (ImageHeight(image) / 2); y++)
                        {
                                for(x = 0; x < ImageWidth(image); x++)
                                {
                                        tmpR = GetPixelR(image, x, (ImageHeight(image) - 1) - y);
                                        tmpG = GetPixelG(image, x, (ImageHeight(image) - 1) - y);
                                        tmpB = GetPixelB(image, x, (ImageHeight(image) - 1) - y);

                                        SetPixelR(image, x, (ImageHeight(image) - 1) - y, GetPixelR(image, x, y));
                                        SetPixelG(image, x, (ImageHeight(image) - 1) - y, GetPixelG(image, x, y));
                                        SetPixelB(image, x, (ImageHeight(image) - 1) - y, GetPixelB(image, x, y));

                                        SetPixelR(image, x, y, tmpR);
                                        SetPixelG(image, x, y, tmpG);
                                        SetPixelB(image, x, y, tmpB);
                                }//for x
                        }//for
			DeleteImage(Temp_Image);
                        return image;
			break;
		
		case 3: 
			printf("90 degree right turn selected\n");
			
			for(x = 0; x < ImageHeight(image); x++)
			{
				for(y = 0; y < ImageWidth(image); y++)
				{

					tmpR = GetPixelR(image, y, x);
					tmpG = GetPixelG(image, y, x);
					tmpB = GetPixelB(image, y, x);

					SetPixelR(Temp_Image, (ImageHeight(image)- 1) - x, y, tmpR);
					SetPixelG(Temp_Image, (ImageHeight(image)- 1) - x, y, tmpG);
					SetPixelB(Temp_Image, (ImageHeight(image)- 1) - x, y, tmpB);
				}
			}
			DeleteImage(image);
			return Temp_Image;
			break;
		
		case 4:
			printf("90 degree left turn selected\n");
			
			for(x = 0; x < ImageHeight(image); x++)
			{
				for(y = 0; y < ImageWidth(image); y++)
				{
					tmpR = GetPixelR(image, y, x);
                                        tmpG = GetPixelG(image, y, x);
                                        tmpB = GetPixelB(image, y, x);

                                        SetPixelR(Temp_Image,  x, (ImageWidth(image)- 1) - y, tmpR);
                                        SetPixelG(Temp_Image,  x, (ImageWidth(image)- 1) - y, tmpG);
                                        SetPixelB(Temp_Image,  x, (ImageWidth(image)- 1) - y, tmpB);					
				}
			}
			DeleteImage(image);
			return Temp_Image;
			break;
	}//switch
	DeleteImage(image);
	return Temp_Image;
}



void matrix_3_3multiplyVector_3(float vector[3], const float matrix[3][3])
{
	// Memory for result 
	float result[3] = {0, 0, 0};

	// Perform multiplication 
	result[0] = matrix[0][0]*vector[0] + matrix[0][1]*vector[1] + matrix[0][2]*vector[2];
	result[1] = matrix[1][0]*vector[0] + matrix[1][1]*vector[1] + matrix[1][2]*vector[2];
	result[2] = matrix[2][0]*vector[0] + matrix[2][1]*vector[1] + matrix[2][2]*vector[2];

	// Copy result into other stack's memory 
	vector[0] = result[0];
	vector[1] = result[1];
	vector[2] = result[2];
}

IMAGE *HueRotate(IMAGE *image, float angle)
{
	assert(image);
	
	// Matrix to transform normalized
	// RGB color vector from the RGB
	// color space to the YIQ color space 
	static const float RGBtoYIQMatrix[3][3] = {{0.299,  0.587,  0.114},
								  			   {0.596, -0.274, -0.321},
								  			   {0.211, -0.523,  0.311}};

	// Matrix to transform normalized
	// YIQ color vector from the YIQ
	// color space to the RGB color space 
	static const float YIQtoRGBMatrix[3][3] = {{1.000,  0.956,  0.621},
								  			   {1.000, -0.272, -0.647},
								  			   {1.000, -1.107,  1.705}};

	const float cs = cos(angle), ss = sin(angle);

	// Matrix to perform a hue
	// rotation on a normalized
	// YIQ color vector
	const float XYPlaneVectorRotateMatrix[3][3] = {{1.000, 0.000, 0.000},
												   {0.000, cs, -ss},
												   {0.000, ss, cs}};

	// Image variables 
	float temp[3];

	for(unsigned int x = 0; x < ImageWidth(image); x++)
	{
		for(unsigned int y = 0; y < ImageHeight(image); y++)
		{
			// Create a normalized RGB color
			// vector fro the current pixel
			// in the image 
			temp[0] = (float)GetPixelR(image, x, y) /255;
			temp[1] = (float)GetPixelG(image, x, y) /255;
			temp[2] = (float)GetPixelB(image, x, y) /255;

			// Transform the RGB vector
			// to a YIQ vector 
			matrix_3_3multiplyVector_3(temp, RGBtoYIQMatrix);

			// Perform the DIP
			matrix_3_3multiplyVector_3(temp, XYPlaneVectorRotateMatrix);

			// Transform back to RGB 
			matrix_3_3multiplyVector_3(temp, YIQtoRGBMatrix);

			// Denormalize and store back into the image 
			temp[0] = temp[0] * 255;
			temp[0] = temp[0] < 0 ? 0 : temp[0];
			temp[0] = temp[0] > 255 ? 255 : temp[0];
			temp[1] = temp[1] * 255;
			temp[1] = temp[1] < 0 ? 0 : temp[1];
			temp[1] = temp[1] > 255 ? 255 : temp[1];
                        temp[2] = temp[2] * 255;
                        temp[2] = temp[2] < 0 ? 0 : temp[2];
                        temp[2] = temp[2] > 255 ? 255 : temp[2];

                        SetPixelR(image, x, y, (unsigned char)temp[0]);
                        SetPixelG(image, x, y, (unsigned char)temp[1]);
                        SetPixelB(image, x, y, (unsigned char)temp[2]);
                }
        }
	return image;
}

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
