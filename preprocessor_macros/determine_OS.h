/*
 * determine_OS.h
 *
 *  Created on: Aug 17, 2010
 *      Author: Stefan
 */

#ifndef DETERMINE_OS_H_
#define DETERMINE_OS_H_

#ifdef _WIN32 //built-in define under MinGW
  #ifndef _WINDOWS
    #define _WINDOWS
  #endif
#endif

#endif /* DETERMINE_OS_H_ */
