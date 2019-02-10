//image_processing.h written by Aidan Coopman Nov 2017

#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H


#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdint.h> //this defines uint8_t

void flip_image(uint8_t * image, int height, int width);
void flip_pixels(uint8_t * image, int height, int width);
void domain_pixels(uint8_t * image, int height, int width);
void black_out_even_lines(uint8_t * image, int height, int width);
void blur_image(uint8_t * image, uint8_t * out_image, int height, int width);
void subtract_image(uint8_t * in1, uint8_t * in2, uint8_t * out, int height, int width);
void add_image(uint8_t * image, uint8_t * detail, uint8_t * out, int height, int width, float factor);
int find_sharpness(uint8_t * image, int height, int width);

#endif
