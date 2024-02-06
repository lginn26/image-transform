/**********************
 * Louis Godfrey
 * CPSC 2310 Section 001
 * lagodfr@clemson.edu
 **********************/

#include "functions.h"

// Images are allocated in memory as height(top to bottem) 
// by width(left to right) to make reading and writing data
// simpler


pixel** allocateImage(ppm_head head)
{
	// Determine the dimensions of the image
	int rows = head.height, columns = head.width;
	// Allocate memory for each row in the image
	pixel **image = (pixel **)malloc(rows * sizeof(pixel*));
	// Allocate memory for each column
	for (int row = 0; row < rows; row++)
	{
		image[row] = (pixel *)malloc(columns * sizeof(pixel));
	}
	return image;
}

void deallocateImage(ppm_head head, pixel** image)
{
	// Free memory held by columns of image
	for (int index = 0; index < head.height; index++)
	{
		free(image[index]);
	}
	// Free memory held by rows of image
	free(image);

}

void detectComments(FILE* in_file)
{
	// The character most recently read
	char readChar = fgetc(in_file);
	// Keep reading until a comment or numerical data is reached
	while ((readChar < 48 || readChar > 57))
	{
		// If a comment was found, discard it
		if (readChar == '#')
		{
			discardComments(in_file);
		}
		readChar = fgetc(in_file);
	}

	// Assuming next byte is numerical, return the read char
	ungetc(readChar, in_file);
}

void discardComments(FILE* in_file)
{
	// The character most recently read
	char readChar = fgetc(in_file);
	// read until the end of the comment is reached
	while (readChar != '\n')
	{
		readChar = fgetc(in_file);
	}
}

ppm_head readImageHeader(FILE* in_file)
{
	// The header that is to be filled from data in in_file
	ppm_head imageHeader;
	// Read in the ppm format
	fscanf(in_file, "%s", imageHeader.ppmType);
	// Discard comments
	detectComments(in_file);
	// Read in the image width
	fscanf(in_file, "%i", &imageHeader.width);
	// Discard comments
	detectComments(in_file);
	// Read in the image height
	fscanf(in_file, "%i", &imageHeader.height);
	// Discard comments
	detectComments(in_file);
	// Read in the color constant
	fscanf(in_file, "%i", &imageHeader.colorConstant);
	// Discard comments
	discardComments(in_file);
	// Return filled header
	return imageHeader;
}

ppm_head generateImageHeader(ppm_head old_head)
{
	// The new image's width
	double rWidth = 0;
	// The new image's height
	double rHeight = 0;

	// Prompt user for the reduction/growth value of the new image's 
	// width. Reprompt if the given number will produce a negative
	// width
	while (rWidth <= 0)
	{
		printf("Provide the change value for the new image's width: ");
		scanf("%lf", &rWidth);
		rWidth = old_head.width + rWidth;
		if (rWidth > 0)
		{
			break;
		}
		printf("Provided number will produce a negative width!");
	}

	// Prompt user for the reduction/growth value of the new image's 
	// height. Reprompt if the given number will produce a negative
	// width
	while (rHeight <= 0)
	{
		printf("Provide the change value for the new image's height: ");
		scanf("%lf", &rHeight);
		rHeight = old_head.height + rHeight;
		if (rHeight > 0)
		{
			break;
		}
		printf("Provided number will produce a negative height!");
	}

	ppm_head returnedHead = old_head;
	returnedHead.width = rWidth;
	returnedHead.height = rHeight;
	return returnedHead;
}

void writeImageHeader(FILE* out_file, ppm_head head)
{
	fprintf(out_file, "%s\n%i\n%i\n%i\n",
			head.ppmType,
			head.width,
			head.height,
			head.colorConstant);
}

void readImagePixels(FILE* in_file, pixel** pixel_container, ppm_head head)
{
	// For each row of pixels in the original image
	// populate the corrosponding row in pixel_container
	for (int row = 0; row < head.height; row++)
	{
		fread(pixel_container[row], sizeof(pixel) * head.width,
		1, in_file);
	}
}

void writeImagePixels(FILE* out_file, pixel** pixels, ppm_head head)
{
	for (int row = 0; row < head.height; row++)
	{
		fwrite(pixels[row], head.width * sizeof(pixel), 1, out_file);
	}
}

pixel** negativeImage(pixel** old_image, ppm_head head)
{
	// Allocate a container for the negative image's pixels
	pixel** negativeImage = allocateImage(head);
	// For every pixel in the new image populate negativeImage
	for (int row = 0; row < head.height; row++)
	{
		for (int column = 0; column < head.width; column++)
		{
			// Set the color value of the corrosponding pixel
			// so its the inverse of the orginial
			negativeImage[row][column].red = 
				255 - old_image[row][column].red;
			negativeImage[row][column].green = 
				255 - old_image[row][column].green;
			negativeImage[row][column].blue = 
				255 - old_image[row][column].blue;
		}	
	}
	// Return the container
	return negativeImage;
}

pixel** resizeImage(pixel** old_image,
		ppm_head head,
	       	ppm_head resizedHeader)
{
	// Width scale factor
	double widthSF = 
		((double) head.width / (double) resizedHeader.width);
	// Height scale factor
	double heightSF = 
		((double) head.height / (double) resizedHeader.height);
	// Pixel data of the resized image	
	pixel** resizedImage = allocateImage(resizedHeader);

	// For each pixel in the new image's pixel container
	// Set the value of each pixel
	for (int row = 0; row < resizedHeader.height; row++)
	{
		for (int column = 0; column < resizedHeader.width; column++)
		{
			resizedImage[row][column] =
			old_image[ (int) (row * heightSF)]
			[ (int) (column * widthSF)];
		}
	}
	return resizedImage;
}
