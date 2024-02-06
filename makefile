compile:
	gcc driver.c functions.c -g 
	./a.out input.ppm resized.ppm negative.ppm

clean:
	rm *.out
	rm negative.ppm
	rm resized.ppm
