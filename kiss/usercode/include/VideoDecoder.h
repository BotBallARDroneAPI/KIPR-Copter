/// VideoDecoder.h

#ifndef VIDEODECODER_H
#define VIDEODECODER_H

#include <vector>
#include <cstring>
#include <cstdio>

#define buffersize 921600 //640x480x3 MAX out

namespace ARDrone
{
  namespace VideoDecoder
  {
    struct Image
    {
      unsigned char data[buffersize]; 
      int width;
      int height;
    };
    
    bool decodeImage(unsigned char* stream, unsigned int streamLength, ARDrone::VideoDecoder::Image& resultImage);
  }  //namespace VideoDecoder
}//namespace ARDrone

#endif
