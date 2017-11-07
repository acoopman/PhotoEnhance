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
  
  string text = "Dong";
  string outfile = "out.jpg";
  cout << "the number of input arguments is = " << argc << endl;
  for(int i = 0; i< argc; i++)
    {
      cout << argv[i] << endl;
    }
  
  int temporary;
  if( argc < 2)
    {
     cout <<" Usage: display_input InputToLoadAndDisplay" << endl;
     return -1;
    }
  int switchs = 0;
  if (argc >2)
    {
      switchs = atoi(argv[2]);
    }
  if(argc > 3)
    {
      outfile = argv[3];
    }
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

#if 0
    int  pixel;
    int hscale = 1;
    int vscale = 1;
    //go through the image
    if(switchs == 0)
      {
	flip_image(image, height, width);
      }
    else if(switchs==1)
      {
	flip_pixels(image, height, width);
      }
    else
      {
	domain_pixels(image, height, width);
      }

    string txt = "hey, I farted";
    Point center(width/2, height/2);
    circle(gray,center, 10, Scalar(255,0,0));
    circle(gray,Point((width/2)+20,height/2), 10, Scalar(255,0,0));
    circle(gray,Point((width/2)+10,(height/2)-20), 10, Scalar(255,0,0));
    circle(gray,Point((width/2)+10,height/2-40), 10, Scalar(255,0,0));
    circle(gray,Point((width/2)+10,height/2-60), 10, Scalar(255,0,0));
    putText(gray, txt, Point(width/2-80,height/2+40), FONT_HERSHEY_SIMPLEX , 1, Scalar(255,0,0));
    rectangle(gray, Point((width/2)-10,height/2-70), Point((width/2)+30,height/2+10), Scalar(255,0,0));
#endif

    //----------------------------
    //Aidan define this function
    //  black_out_even_lines(image, height, width);
    //--------------------------
    find_sharpness(image, height, width);

    //define this Aidan
    blur_image(image,out_image,height,width);
    imshow( "BLUR", gray );
    //out_image2[] = image[]-out_image[] 
    subtract_image(image,out_image,out_image2,height,width); //detail
    imshow( "DETAIL", output2 );
    add_image(image,out_image2,out_image,height,width, 1.2);
    imshow( "EDGE ENHANCE", output );
    
    find_sharpness(out_image, height, width);
    
    //imshow( "Gray OUT", gray );

    //imshow( "OUTPUT2", output2 );
    imwrite(outfile, gray);
    
    waitKey(0);

    
    return 0;
}
