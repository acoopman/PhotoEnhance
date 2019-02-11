//photo_enhance.cpp written by Aidan Coopman Feb 2019
//https://github.com/acoopman/PhotoEnhance

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "image_processing.h"

using namespace cv;
using namespace std;

//----------------------------------------------------------------------------
int main( int argc, char** argv )
{

  //default output file is out.jpg
  string outfile = "out.jpg";

  //tell the user how to use the program
  if( argc < 2)
    {
     cout <<" Usage: photo_enhance input_file.jpg [default out.jpg]" << endl;
     return -1;
    }

  //read in the image
  Mat input;
  input = imread(argv[1], CV_LOAD_IMAGE_COLOR);
  
  // Check for invalid input
  if(! input.data )                              
    {
      cout <<  "Could not open or find the input" << std::endl ;
      return -1;
    }

  //get height and width
  int width  =  input.cols;
  int height =  input.rows;
  cout << "Input size is "<< width << "x" << height << endl;
  cout << "input file is " << argv[1] << " output file is " << outfile << endl;
  
  //conver the input to Black and white (gray input):
  // Create a new matrix to hold the gray input
  Mat gray;
  Mat output;
  Mat output2;
  
  // convert RGB input to gray
  cvtColor(input, gray, CV_RGB2GRAY);
  cvtColor(0*input, output, CV_RGB2GRAY);
  cvtColor(0*input, output2, CV_RGB2GRAY);
  
  //show the input
  imshow( "Gray Input", gray );

  //PIPELINE
  //******************************************************************************************
  //******************************************************************************************
  //IMAGE MODIFIED
  uint8_t  * image     = gray.data;
  uint8_t  * out_image = output.data;
  uint8_t  * out_image2 = output2.data;

  //Domain Extension Module
  //Step 1, extend the domain of the pixels to cover 0-255
  domain_pixels(image, height, width);
  imshow( "Step 1: Domain Extension", gray );

  //check sharpness before edge enhance
  int sharpness = find_sharpness(image, height, width);
  cout << "Sharpness before enhance = " << sharpness << endl;    

  //Edge Enhancement Module
  //Step 2, blur the image
  blur_image(image,out_image,height,width);
  imshow( "Step 2: Blur", gray );

  //Step 3, subtract the blur from the image to get detail
  subtract_image(image,out_image,out_image2,height,width); //detail
  imshow( "Step 3: Detail", output2 );

  //Step 4, add the detail to the image
  add_image(image,out_image2,out_image,height,width, 1.2);
  imshow( "Step 4: Add Detail = FINAL OUTPUT", output );

  //check sharpness again
  sharpness = find_sharpness(out_image, height, width);
  cout << "Sharpness after  enhance = " << sharpness << endl;    
  //******************************************************************************************
  //******************************************************************************************
  
  //write the final enhanced file to output
  imwrite(outfile, output);
  
  waitKey(0);
  
  return 0;
}
