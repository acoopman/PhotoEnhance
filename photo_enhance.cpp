//Project is at:
//https://github.com/acoopman/PhotoEnhance
//image_main.cpp

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
  
  string outfile = "out.jpg";
  if( argc < 2)
    {
     cout <<" Usage: photo_enhance input_file.jpg" << endl;
     return -1;
    }
  //if(argc > 2)
  //{
  //  cout << "here\n";
  //  outfile = argv[3];
  //}
    Mat input;
    input = imread(argv[1], CV_LOAD_IMAGE_COLOR);   // Read the file

    if(! input.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the input" << std::endl ;
        return -1;
    }

    int width  =  input.cols;
    int height =  input.rows;

    cout << "Input size is "<< width << "x" << height << endl;
    cout << "input file is " << argv[1] << " output file is " << outfile << endl;

    //conver the input to Black and white (gray input): -----------------------------------------------
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
    waitKey(0);
 
    //-------------------------------------------------------------------------------------------
    //******************************************************************************************
    //******************************************************************************************
    //******************************************************************************************
    //IMAGE MODIFIED
    //    uint8_t  * image = gray.data;
    uint8_t  * image     = gray.data;
    uint8_t  * out_image = output.data;
    uint8_t  * out_image2 = output2.data;

    domain_pixels(image, height, width);
    imshow( "domain extension", gray );

    int sharpness = find_sharpness(image, height, width);
    cout << "Sharpness before enhance = " << sharpness << endl;    

    blur_image(image,out_image,height,width);
    imshow( "BLUR", gray );
    
    subtract_image(image,out_image,out_image2,height,width); //detail
    imshow( "DETAIL", output2 );
    
    add_image(image,out_image2,out_image,height,width, 1.2);
    imshow( "EDGE ENHANCE", output );
    
    sharpness = find_sharpness(out_image, height, width);
    cout << "Sharpness after enhance = " << sharpness << endl;    
    
    imwrite(outfile, output);
    
    waitKey(0);
    
    return 0;
}
