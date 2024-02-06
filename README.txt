Submittion By: Louis Godfrey

What this project is:
This is a simple image manipulation program written in C. It intakes a .ppm
file named "input.ppm" and outputs two image files each with their own
tranformation. The first is an image resized to given user input. The other
is a negative coloration of the input.

How to run:
1. Optional: Load a .ppm file into the current directory named "input.ppm"
2. Run "make compile" to compile the program
3. Run "make run" to run the program
4. Provide valid input as instructed

Running the program should output two transformed .ppm images.

Problems:
1. This wasn't so much as a problem, but rather a difficult decision to make.
I was on the fence on the order I should allocate my pixels; rows then columns
or columns then rows. I ultimatly decided rows then columns would be the best 
option because of how PPM images are formatted Allocating rows as the pixel
pointers and the columns as pixels made the most sense since I could break up
rows as they were being read.

2. Somthing strange was happeing when generating the header for my resized
image. The image would be unopenable on the virtual machine since garbage
binary data was being appended after the P6, making the ppm format 
unrecognizable. I may had something to do with the way the header struct was 
allocated, but I honestly couldn't tell you why. I solved the problem by using
copy assigment from the old header to the new and manually setting the new 
width and height values.

3. After correcting the header issue, I relized my pixels were not being
written correctly. My program would output a correctly resized image, but the
entire image would just be a solid color of the first pixel read. After some
debugging, I relized widthSF and heightSF were being set to 0 because I was
dividing two int thus truncating the number. I was able to cast both
the old and new width and height to a double and my resized worked perfectly.

Praises & Critiques
- Honestly, this project was both interesting and fun. I only have a couple of
  minor critisisms.
- I appriciate being told how to implement our a image filters. Otherwise, this
  project would've a lot longer due to the time figuring out the algorithums. 
- I suggest using 
 standard function header used by most programers which utilzies @params and
 @returns. For example, the comment for the resizeImage function could've been 
 written like this.

/* 
 * This function intakes the header of the new image and the pixel data of the
 * old image and generates a new image scaled to width and height values
 * specified by the user. Scaled values are prompted for during runtime
 *
 * @param old_image A dynamically allocated 2D array of pixel structs
 * containing the pixel data of the original image
 * @param head A ppm_head struct containing the original image's header
 * @param resized_img_head A ppm_head struct containing the header data
 * 
 * @return A dynamically allocated 2D array of pixels containing the pixel
 * data of the newly sized image
 */ 
