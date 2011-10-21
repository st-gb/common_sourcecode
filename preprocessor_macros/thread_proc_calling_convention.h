/*
 * thread_proc_calling_convention.h
 *
 *  Created on: 28.09.2011
 *      Author: Stefan
 */

#ifndef THREAD_PROC_CALLING_CONVENTION_H_
#define THREAD_PROC_CALLING_CONVENTION_H_

#ifdef _WIN32 //Built-in macro for MSVC, MinGW (also for 64 bit Windows)
  #define THREAD_PROC_CALLING_CONVENTION WINAPI
#else
  #define THREAD_PROC_CALLING_CONVENTION /* -> empty string */
#endif

#endif /* THREAD_PROC_CALLING_CONVENTION_H_ */
