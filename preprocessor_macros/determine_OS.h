/*
 * determine_OS.h
 *
 *  Created on: Aug 17, 2010
 *      Author: Stefan
 */

#ifndef DETERMINE_OS_H_
#define DETERMINE_OS_H_

#ifdef _WIN32 //Built-in macro for MSVC, MinGW (also for 64 bit Windows)
  #ifndef _WINDOWS
    #define _WINDOWS
  #endif
#endif

#endif /* DETERMINE_OS_H_ */
