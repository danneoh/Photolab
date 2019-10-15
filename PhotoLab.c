/*********************************************************************/
/* PhotoLab.c: homework assignment #3, for EECS 22,  Fall 2017       */
/* Modified: Mihnea Chirila for F18, 10/30/18                                                          */
/* Author: Mina Moghadam                                                */
/* Date:   11/8/2017                                                */
/*                                                                   */
/* Comments: */
/*                                                                   */
/* Please use this template to submit your hw3.                      */
/*********************************************************************/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "DIPs.h"
#include "Advanced.h"
#include "FileIO.h"
#include "Constants.h"
#include "Image.h"
#include "Test.h"

/*** function declarations ***/

/* print a menu */
void PrintMenu();

int main()
{
#ifdef DEBUG
	AutoTest();
#else

	int option;			/* user input option */
	char fname[SLEN];		/* input file name */
	int brightness = -256;
	float angle;
	int percentage;
	float percent;
        IMAGE *image = NULL;	
	IMAGE *rc = NULL;

	while (option != EXIT) 
	{
		if (option == 1) 
		{
			printf("Please input the file name to load: ");
			scanf("%s", fname);
			rc = LoadImage(fname);
		}

		/* menu item 2 - 8 requires image is loaded first */
        else if (option >= 2 && option <= 12) {
            if (image != SUCCESS)	 
	    {
                printf("No image is read.\n");
            }
            /* now image is loaded */
            else {
			switch (option) {
			case 2:
				printf("Please input the file name to save: ");
				scanf("%s", fname);
				SaveImage(fname, rc);
				break;
			case 3:
				BlackNWhite(rc);
				printf("\"Black & White\" operation is done!\n");
				break;
			case 4:
				Edge(rc);
			        printf("\"Edge\" operation is done!\n");
				break;
			case 5:
				Shuffle(rc);
				printf("\"Shuffle\" operation is done!\n");
				break;
			case 6:
				while(brightness > 255 || brightness < -255)
				{
					printf("Enter brightness value (between -255 and 255):\n");
					scanf("%d", &brightness);
				}
				Brightness(rc, brightness);
				printf("\"brightness\" operation is done!\n");
				break;
			case 7:
				HMirror(rc);
				printf("\"Horizontally Mirror\" operation is done!\n");
				break;
			case 8:
				printf("Enter hue rotation angle:\n");
				scanf("%f", &angle);
				HueRotate(rc, angle);
				printf("\"HueRotate\" operation is done!\n");
				break;
			
			case 9:
				printf("How would you like to flip the image?\n");
				printf("Options are as follows:\n");
				printf("1: Horizontal Flip\n2: Vertical Flip\n3: Rotate 90 degrees to the right\n4: Rotate 90 degrees to the left\n");
				scanf("%d", &option);
				rc = Rotate(rc, option);
				printf("\"Rotate\" operation is done!\n");
				break;
			
			case 10:
				printf("Please enter the percentage you would like to rescale\n");
				scanf("%d", &percentage);
				rc = Resize(rc, percentage);
				printf("\"Resize\" operation is done!\n");
				break;

			case 11:

				printf("Please enter the percentage of saturation you would like\n");
				scanf("%f", &percent);
				Saturate(rc, percent);
				printf("\"Saturate\" operation is done!\n");
				break;
			
			case 12:
				AutoTest();
				break;			
		
			case 13:
				printf("Goodbye!\n");
				exit(0);
				break;

			default:
				break;

				}
			}
		}
        else {
            printf("Invalid selection!\n");
        }

		/* Process finished, waiting for another input */
        PrintMenu();
        printf("Please make your choice: ");
        scanf("%d", &option);
	}
	
	printf("You exit the program.\n");
	if(rc!=NULL){	
	DeleteImage(rc);
	rc = NULL;}
#endif
	
	
	return 0;
}


/*******************************************/
/* Function implementations should go here */
/*******************************************/

/* Menu */
void PrintMenu() 
{
    printf("\n----------------------------\n");
    printf(" 1: Load a PPM image\n");
    printf(" 2: Save an image in PPM and JPEG format\n");
    printf(" 3: Change a color image to Black & White\n");
    printf(" 4: Sketch the edge of an image\n");
    printf(" 5: Shuffle an image\n");
    printf(" 6: Adjust the brightness of an image\n");
    printf(" 7: Mirror an image horizontally\n");
    printf(" 8: Adjust the hue of an image\n");
    printf(" 9: Rotate or flip the image\n");
    printf("10: Resize the image\n");
    printf("11: Saturate the image\n");	
    printf("12: Test all functions\n");
    printf("13: Exit\n");
}


/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
