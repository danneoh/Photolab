#ifndef ADVANCED_H_INCLUDED_
#define ADVANCED_H_INCLUDED_


#include "Constants.h"
#include "Image.h"

/* Adjust the brightness of an image */
IMAGE *Brightness(IMAGE *image, int brightness);

/* Mirror an image horizontally */
IMAGE *HMirror(IMAGE *image);

/* Adjust the saturation of an image*/
IMAGE *Saturate(IMAGE *image, float percent);

void matrix_3_3multiplyVector_3(float vector[3], const float matrix[3][3]);

/* Adjust the hue of an image*/
IMAGE *HueRotate(IMAGE *image, float angle);

/* Adjust the size of an image*/
IMAGE *Resize(IMAGE *image, int percentage);

/* Adjust the rotation of a photo*/
IMAGE *Rotate(IMAGE *image, int option);
#endif /* ADVANCED_H_INCLUDED_ */

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
