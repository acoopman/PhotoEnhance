# Makefile written by Aidan Coopman
# Feb 1, 2019 for photo enhance


CC = g++
CFLAGS = -Ofast -fPIC -Wall -std=c++0x
INCLUDES = -I./
OPENCV_CFLAGS = `pkg-config opencv --cflags`
OPENCV_LIBS = `pkg-config opencv --libs`
INCLUDES += $(OPENCV_CFLAGS) $(FFTW_CFLAGS)
LIBS = $(OPENCV_LIBS) $(FFTW_LIBS)

#find all the source files
HDRS = image_processing.h
SRCS = photo_enhance.cpp image_processing.cpp
PROG = photo_enhance


all: $(PROG)

#------------------------------------------------------------------------------------------------------------------------------------------------
$(PROG): $(SRCS) $(HDRS)
	$(CC) $(SRCS) $(CFLAGS) $(INCLUDES)  -o  $(PROG) $(LIBS)

clean:
	rm -f $(PROG)
