/// ATCommand.h
#ifndef ATCOMMANND_H
#define ATCOMMANND_H

#include <string>

namespace ARDrone
{
	/**
	 @brief This structure defines structure of a ARDrone ATCommand
	 **/
  struct ATCommand 
  {
    std::string strCommandHeader;
    std::string strCommandData;
  };
}//namespace ARDrone

#endif