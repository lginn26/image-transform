/**********************
 * Louis Godfrey
 * CPSC 2310 Section 001
 * lagodfr@clemson.edu
 **********************/

#include "functions.h"
#include <assert.h>

int main(int argc, char** argv)
{
	// Ensure a input, negative, and resized filename 
	assert(argc == 4);
	// Open the input image
	FILE* inputPPM = fopen(argv[1], "rb");
	assert(inputPPM != NULL);
	// Read in the header of the input image
	ppm_head inputHeader = readImageHeader(inputPPM);
	// Allocate memory for the input image
	pixel** inputImage = allocateImage(inputHeader);
	// Read in the pixel data from our input into container inputImage
	readImagePixels(inputPPM, inputImage, inputHeader);
	// Open/create the output image with the negative filter
	FILE * negativeOutputPPM = fopen(argv[3], "ab");
	assert(negativeOutputPPM != NULL);
	// Generate pixel data for the negative image
	pixel** imageNegative = negativeImage(inputImage, inputHeader);
	// Write the negative image data to our negative output image
	writeImageHeader(negativeOutputPPM, inputHeader);
	writeImagePixels(negativeOutputPPM, imageNegative, inputHeader);
	// Open/Create the output file for the resized image
	FILE * resizedOutputPPM = fopen (argv[2], "ab");
	assert(resizedOutputPPM != NULL);
	// Generate the header data for the resized image
	ppm_head resizedHeader = generateImageHeader(inputHeader);
	// Generate the pixel data for the resized image
	pixel** imageResize = resizeImage(inputImage, inputHeader,
		       resizedHeader);
	// Write the resized image data to our resized output image
	writeImageHeader(resizedOutputPPM, resizedHeader);
	writeImagePixels(resizedOutputPPM, imageResize, resizedHeader);
	// Deallocate Memory for all images
	deallocateImage(inputHeader, inputImage);
	deallocateImage(inputHeader, imageNegative);
	deallocateImage(resizedHeader, imageResize);
	// Close all files
	fclose(inputPPM);
	fclose(negativeOutputPPM);
	fclose(resizedOutputPPM);
}
