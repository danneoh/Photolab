######################################################################
# Makefile: Makefile for Assignment #3 EECS22 Fall 2018
#
# 10/30/18 Mihnea Chirila: updated for EECS22 Assignment 3 Fall 2018
#
######################################################################


# design names
DESIGN = PhotoLab PhotoLabTest

#libs
LIBS   = libFilter.a

CC     = gcc
DEBUG  = -DDEBUG
CFLAGS = -ansi -std=c99 -Wall -g -c
LFLAGS = -ansi -std=c99 -Wall -lm
AR     = ar rc
RANLIB = ranlib

IMAGES = bw.ppm \
         edge.ppm \
         shuffle.ppm \
	 brightness.ppm \
         hmirror.ppm \
         hue.ppm \ 




all: PhotoLab PhotoLabTest


########### generate object files ###########

#target to generate FileIO.o
FileIO.o: FileIO.h FileIO.c Constants.h
	$(CC) $(CFLAGS) FileIO.c -o FileIO.o

#target to generate DIPs.o
DIPs.o: DIPs.h DIPs.c Constants.h
	$(CC) $(CFLAGS)  DIPs.c -o DIPs.o

#target to generate Advanced.o
Advanced.o: Advanced.h Advanced.c Constants.h
	$(CC) $(CFLAGS) Advanced.c -o Advanced.o


#target to generate Image.o
Image.o: Image.h Image.c Constants.h
	$(CC) $(CFLAGS) Image.c -o Image.o

#target to generate PhotoLab.o
PhotoLab.o: PhotoLab.c DIPs.h Advanced.h FileIO.h Constants.h
	$(CC) $(CFLAGS) PhotoLab.c -o PhotoLab.o

#target to generate FileIO_DEBUG.o
PhotoLab_DEBUG.o: PhotoLab.c DIPs.h Advanced.h FileIO.h Constants.h
	$(CC) $(CFLAGS) $(DEBUG) -c PhotoLab.c -o PhotoLab_DEBUG.o

Test.o: Test.c Test.h Constants.h
	$(CC) $(CFLAGS) Test.c -o Test.o


########### generate library files ###########

#target to generate libFilter.a
libFilter.a: DIPs.o Advanced.o
	$(AR) libFilter.a Advanced.o DIPs.o
	$(RANLIB) libFilter.a


########### generate executables ###########

#target to generate PhotoLab
PhotoLab: PhotoLab.o FileIO.o libFilter.a Image.o DIPs.h Test.o
	$(CC) $(LFLAGS) PhotoLab.o FileIO.o Image.o Test.o -L. -lFilter -o PhotoLab

#target to generate test
PhotoLabTest: PhotoLab_DEBUG.o FileIO.o libFilter.a Image.o Test.o
	$(CC) $(LFLAGS) PhotoLab_DEBUG.o FileIO.o Image.o Test.o -L. -lFilter -o PhotoLabTest
	
#target to clean the directory
clean:
	rm -f *.o *.jpg rotate.ppm saturate.ppm hflip.ppm bigresize.ppm smallresize.ppm $(DESIGN) $(IMAGES) $(LIBS)

