/*
 * GetCurrentReferenceClock.hpp
 *
 *  Created on: Jun 4, 2010
 *      Author: Stefan
 */
//This file is intellectual property of Trilobyte SE GmbH, Berlin, Germany.
//Copyright 2010 by Trilobyte SE GmbH, Berlin, Germany.
//It must not be used commercially without the permission of Trilobyte
//SE GmbH, Berlin, Germany.
//It may be used for educational / academic purposes for free.
//If you use (parts) of this sourcecode then this license text must be contained.
#ifndef GETTICKCOUNT_HPP_
#define GETTICKCOUNT_HPP_

#include <stdint.h> //uint64_t
typedef uint64_t TimeCountInNanosec_type;

#if defined (__linux__) || defined(__ANDROID__)
  #include <Linux/time/GetTickCount.hpp>
  #ifndef OPERATING_SYSTEM_NAME
    #define OPERATING_SYSTEM_NAME Linux
  #endif
#endif
#ifdef _WIN32 //Built-in preprocessor macro for MSVC, MinGW (also for 64 bit)
  #include <Windows/time/GetTimeCount.hpp>
  #ifndef OPERATING_SYSTEM_NAME
    #define OPERATING_SYSTEM_NAME Windows
  #endif
  /** from http://www.cprogramming.com/tutorial/namespaces.html */
//  namespace OperatingSystem = Windows;
#endif

namespace OperatingSystem
{
#ifdef _WIN32 //Built-in preprocessor macro for MSVC, MinGW (also for 64 bit)
//  //TODO: all code into #include <Windows/time/GetTimeCount.hpp>
//  using namespace Windows;
  /** Use "inline" for all functions to avoid "multiple definitions" linker  
      error when this file is _expanded_ multiple times in source code.*/
  inline DWORD GetTimeCountInMilliSeconds(){
    return Windows_API::GetTimeCountInMilliSeconds(); }
  inline bool GetTimeCountInSeconds(//LARGE_INTEGER *lpPerformanceCount
    long double & TimeCountInSeconds )
  {
    return Windows_API::GetTimeCountInSeconds(TimeCountInSeconds);
  }
  inline bool GetTimeCountInNanoSeconds(//LARGE_INTEGER *lpPerformanceCount
    TimeCountInNanosec_type & TimeCountInNanoSeconds  )
  {
    return Windows_API::GetTimeCountInNanoSeconds(TimeCountInNanoSeconds);
  }
#else
  inline bool GetTimeCountInNanoSeconds(//LARGE_INTEGER *lpPerformanceCount
    TimeCountInNanosec_type & TimeCountInNanoSeconds  )
  {
	return Linux::GetTimeCountInNanoSeconds(TimeCountInNanoSeconds);
  }
    inline DWORD GetTimeCountInMilliSeconds(){
      return Linux::GetTimeCountInMilliSeconds(); }
    inline bool GetTimeCountInSeconds(long double & TimeCountInSeconds)
      { return Linux::GetTimeCountInSeconds(TimeCountInSeconds); }
#endif
}//namespace OperatingSystem

#endif //#ifndef GETTICKCOUNT_HPP_
