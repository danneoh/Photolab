/*****************************************************************************/
/* Image.c is the source file for the definition of functions in Image.h     */
/*****************************************************************************/

#include "Image.h"
#include <stdlib.h>
#include <assert.h>
unsigned char GetPixelR(const IMAGE *image, unsigned int x, unsigned int y)
{
	assert(image);
	assert(x <= ImageWidth(image));
	assert(y <= ImageHeight(image));
	assert(image->R);
	return image->R[x + y * ImageWidth(image)];
}

unsigned char GetPixelG(const IMAGE *image, unsigned int x, unsigned int y)
{
        assert(image);
	assert(x <= ImageWidth(image));
        assert(y <= ImageHeight(image));
        assert(image->G);
        return image->G[x + y * ImageWidth(image)];
}

unsigned char GetPixelB(const IMAGE *image, unsigned int x, unsigned int y)
{
        assert(image);
	assert(x <= ImageWidth(image));
        assert(y <= ImageHeight(image));
        assert(image->B);
        return image->B[x + y * ImageWidth(image)];
}

void SetPixelR(IMAGE *image, unsigned int x, unsigned int y, unsigned char r)
{
	assert(x <= ImageWidth(image));
        assert(y <= ImageHeight(image));
	assert(image);
	assert(image->R);
	image->R[x + y * ImageWidth(image)] = r;
}

void SetPixelG(IMAGE *image, unsigned int x, unsigned int y, unsigned char g)
{
        assert(image);
	assert(x <= ImageWidth(image));
        assert(y <= ImageHeight(image));
        assert(image->G);
        image->G[x + y * ImageWidth(image)] = g;
}

void SetPixelB(IMAGE *image, unsigned int x, unsigned int y, unsigned char b)
{
        assert(image);
	assert(x <= ImageWidth(image));
        assert(y <= ImageHeight(image));
        assert(image->B);
        image->B[x + y * ImageWidth(image)] = b;
}


IMAGE *CreateImage(unsigned int Width, unsigned int Height)
{
	IMAGE *imag;
	imag = (IMAGE *)malloc(sizeof(IMAGE));
	
	if(!imag)
	{
		return NULL;
	}
	imag->W = Width;
	imag->H = Height;

	imag->R = (unsigned char *)malloc(Width*Height*(sizeof(unsigned char)));
	if(!(imag->R))
	{
		return NULL;
	}
	
	imag->G = (unsigned char *)malloc(Width*Height*(sizeof(unsigned char)));
	if(!(imag->G))
	{
		return NULL;
	}
	
	imag->B = (unsigned char *)malloc(Width*Height*(sizeof(unsigned char)));
	if(!(imag->B))
	{
		return NULL;
	}


	return imag;
}


void DeleteImage(IMAGE *image)
{
	assert(image);

	assert(image->R);
	assert(image->G);
	assert(image->B);
	
	free(image->R);
	free(image->G);
	free(image->B);

	image->R = NULL;
	image->G = NULL;
	image->B = NULL;
	
	free(image);
}

unsigned int ImageWidth(const IMAGE *image)
{
	return image->W;
}

unsigned int ImageHeight(const IMAGE *image)
{
	return image->H;
}





