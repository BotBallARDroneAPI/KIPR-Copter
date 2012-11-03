#ifndef __COMPAT_H__
#define __COMPAT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <unistd.h>
#include <time.h>
	
	void fsleep(float ftime);
	void msleep(long mtime);
	float seconds();
	
#define sleep(x) fsleep(x)
	
#ifdef __cplusplus
}
#endif

#endif