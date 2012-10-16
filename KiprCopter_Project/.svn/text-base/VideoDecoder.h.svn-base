/// VideoDecoder.h
#include <vector>
#include <cstring>
#include <cstdio>

namespace ARDrone
{
  namespace VideoDecoder
  {
    struct Image
    {
      unsigned char data[921600]; //640x480x3 MAX out
      int width;
      int height;
    };
    
    bool decodeImage(unsigned char* stream, unsigned int streamLength, ARDrone::VideoDecoder::Image& resultImage);
  }  //namespace VideoDecoder
}//namespace ARDrone
