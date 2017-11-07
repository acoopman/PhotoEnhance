#include "image_processing.h"

using namespace std;

//-------------------------------------------------------------------------
void flip_image(uint8_t * image, int height, int width)
{
  int temporary;
  int N = height*width;

     for (int i = 0; i < (N / 2); i++)
       {
	 temporary = image[i];     
	 image[i] = image[(N - 1) - i];
	 image[(N - 1) - i] = temporary;
       }
}
void flip_pixels(uint8_t * image, int height, int width)
{
  int N = height*width;
  int pixel;
     for (int i = 0; i < (N); i++)
       {
         pixel = image[i];
	 image[i] = 255-pixel;
       }
}

void domain_pixels(uint8_t * image, int height, int width)
{
  int min=256;
  int max=0;

  
  for (int i = 0; i<(height*width); i++)
    {
      if(image[i] < min)
	{
	  min = image[i];
	}
      if(image[i] > max)
	{
	  max = image[i];
	}
    }

  

  cout << "min = " << min << endl;
  cout << "max = " << max << endl;

  for (int i = 0; i<(height*width); i++)
    {
      image[i] -= min;
    }
 
  float new_max=max-min;
  float scale = 255.0/new_max;
  for (int i = 0; i<(height*width); i++)
    {
      image[i] = image[i]*scale;
    }
   
}
//---------------------------------------------------------------------------
void black_out_even_lines(uint8_t * image, int height, int width)
{
  
     for (int i = 0; i < height; i++)
       {
	 for( int j =0; j< width; j++)
	   {
	     if((i%2) == 0)
	       image[j+i*width] = 0;
	   }
       }
}

//    blur_image(image,out_image,height,width);
void blur_image(uint8_t * image, uint8_t * out_image, int height, int width)
{
  //first row
  int a,b,c;
  int aa,bb,cc;
  int aaa,bbb,ccc;

  
     for (int i = 0; i < height-3; i++)
       {
	 for( int j =0; j< width-3; j++)
	   {

	     //this is first row of kernel
	     a = image[j+i*width];
	     b = image[j+i*width+1];
	     c = image[j+i*width+2];
	     //2nd
	     aa = image[j+(i+1)*width];
	     bb = image[j+(i+1)*width+1];
	     cc = image[j+(i+1)*width+2];
	     //3rd
	     aaa = image[j+(i+2)*width];
	     bbb = image[j+(i+2)*width+1];
	     ccc = image[j+(i+2)*width+2];



	     out_image[j+i*width]=(a+b+c+aa+bb+cc+aaa+bbb+ccc)/9;
	   }
       }
     
}

// subtract_image(image,out_image,out_image2,height,width);
//---------------------------------------------------------------------------
void subtract_image(uint8_t * in1, uint8_t * in2, uint8_t * out, int height, int width)
{
  int a,b,c;
     for (int i = 0; i < height; i++)
       {
	 for( int j =0; j< width; j++)
	   {
	     a = in1[j+i*width];
	     b = in2[j+i*width];
	     c = a-b;
	     if(c<0)
	       c = 0;
	     out[j+i*width] = c;
	   }
       }
}
//---------------------------------------------------------------------------
void add_image(uint8_t * image, uint8_t * detail, uint8_t * out, int height, int width, float factor)
{
  int a,b,c;
     for (int i = 0; i < height; i++)
       {
	 for( int j =0; j< width; j++)
	   {
	     a = image[j+i*width];
	     b = factor*detail[j+i*width];
	     c = a+b;
	     if(c>255)
	       c = 255;
	     out[j+i*width] = c;
	   }
       }
}

//----------------------------------------------------------------------------
void find_sharpness(uint8_t * image, int height, int width)
{
  int a;
  int b;
  int sharp;
  int max_sharp=-255;
  int min_sharp =255;
  
     for (int i = 0; i < height; i++)
       {
	 for( int j =0; j< (width-1); j++)
	   {
	     a= image[i];
	     b= image[i+1];
	     sharp = a-b;
	     if(sharp > max_sharp)
	       max_sharp = sharp;
	     if(sharp < min_sharp)
	       min_sharp = sharp;
	   }
       }
     cout << "max sharpness = " << max_sharp << endl;
     cout << "min sharpness = " << min_sharp << endl;

}
