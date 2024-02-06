#ifndef FUNCTIONS
#define FUNCTIONS

/**********************
 * Louis Godfrey
 * CPSC 2310 Section 001
 * lagodfr@clemson.edu
 **********************/

#include <stdio.h>
#include <stdlib.h>

// PPM Structs

/*A struct representing a pixel and its three color values*/
typedef struct Pixel {
	unsigned char red;
	unsigned char green;
	unsigned char blue;
} pixel;

/*A struct containing header information of a PPM file*/
typedef struct PPMHeader
{
	char ppmType[2];
	unsigned int width;
	unsigned int height;
	unsigned int colorConstant;
} ppm_head;

// Functions

/* Paramaters: in_file - a file pointer containing a given ppm file
 * Return: output - an instance of ppm_head containing information extracted
 * from in_file's ppm header
 * 
 * This function reads the ppm file passed through in_file. It builds and 
 * returns a instance of ppm_head containing in_file's ppm header data
 */
ppm_head readImageHeader(FILE* in_file);

/* Paramaters: out_file - a file pointer holding a ppm file being built
 * by our program
 * 	       head - an instance of ppm_head containing header information
 * meant to be written into our output ppm file contained by out_file
 * Return: output - Function does not return any values, but modifies 
 * paramater out_file
 * This function intakes a ppm header stored in head and writes the header
 * data to out_file
 */ 
void writeImageHeader(FILE* out_file, ppm_head head);

/* Paramaters: head - an instance of ppm_head whose width and height 
 * 	       data will be referenced during memory allocation 
 * Return: output - Function returns a dynamically allocated 2D array of 
 * pixel structs 
 * This function aids in the proccess of allocating memory for pixel data in
 * a ppm file. It intakes a given header and returns a dynamically allocated
 * 2D array of pixels that is head.width by head.height.
 */
pixel** allocateImage(ppm_head head);

/* Paramaters: head - an instance of ppm_head whose width and height data are
 * 	       referenced during deallocation of memory
 * 	       image - A dynamically allocated 2D array of pixel structs being
 * 	       freed from memory
 * Return: output - Function does not return any values, but frees 
 * memory held in image
 * This function frees the memory held by pixel data of a ppm image within 
 * paramater image.
 */ 
void deallocateImage(ppm_head head, pixel** image);

/* Paramaters: in_file - a file pointer holding the ppm file being read from
 * 	       pixel_container - An empty dynamically allocated 2d array of
 * 	       pixel structs which this function will populate with pixel
 * 	       data from in_file
 * 	       head - a image header refereced to read in the proper number 
 * 	       of pixels
 * Return: output - Function does not return any values, but populates 
 * paramater pixel_container with pixel data read from in_file
 */
void readImagePixels(FILE* in_file, pixel** pixel_container, ppm_head head);

/* Paramaters: out_file - a file pointer holding the ppm file our program is
 * 	       writting to
 * 	       pixels - a dynamically allocated 2D array of pixels whose data
 * 	       will be written to the file within out_file
 * 	       head - a image header referenced to write in the proper number 
 * 	       of pixels
 * Return: output - Function does not return any values, but populates the 
 * pixel data of the file contained in out_file with data from pixels
 *
 */ 
void writeImagePixels(FILE* out_file, pixel** pixels, ppm_head head);

/* Paramaters: old_image - A dynamically allocated 2D array of pixel structs
 * 	       containing the pixel data of the original image
 * 	       head - A ppm_head struct containing the original image's header
 * 	       resized_img_head - A ppm_head struct containing the header data
 * 	       of the newly sized image
 * Return: output - Function returns a dynamcially allocated 2D array of 
 * pixels containing the pixel data of the newly sized image
 * This function intakes the header of the new image and the pixel data of the
 * old image and generates a new image scaled to width and height values 
 * sepcified by the user. Scaled values are prompted for during runtime.
 */ 
pixel** resizeImage(pixel** old_image, ppm_head head,
ppm_head resized_img_head);

/*
 * Paramaters: old_image - A dynamically allocated 2D array of pixel structs
 * 	       contining the pixel data of the orginal image
 * Return: output - Function returns a dynamically allocated 2D array of pixel
 * structs contaning pixel data of the new image
 * This function intakes the pixel data of the original image and applies a 
 * "negative" filter to it. The new image is then returned.
 */ 
pixel** negativeImage(pixel** old_image, ppm_head head);

/* Paramaters: old_head - The header of the original image referenced
 * 	       to produce the new one
 * Return: output - Function returns a ppm_head instance built from the 
 * paramaters and user input
 * This is a helper function which generates a ppm_head instance from 
 * user input and the original header
 */ 
ppm_head generateImageHeader(ppm_head old_head); 

/* Paramaters: in_file - A file pointer contianing the ppm file being read 
 * from
 * Return: output - Function does not return any values, but moves the file 
 * pointer of in_file
 * This function is called when we want to detect comments between needed
 * blocks image data. It makes calls to discardComments when comments are
 * detected.
 */ 
void detectComments(FILE* in_file);

/* Paramaters: in_file - A file pointer containing the ppm file being read 
 * from
 * Return: output - Function does not return any values, but moves the file 
 * pointer of in_file
 * This function is to be called when data unessesary data between desired
 * values needs to be ignored. The function advances the file pointer 
 * forward to the comment's end. 
 */ 
void discardComments(FILE* in_file);
#endif
