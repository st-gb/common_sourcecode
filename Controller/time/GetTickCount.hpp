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

#ifdef __linux__
  #include <Linux/time/GetTickCount.hpp>
#endif
#ifdef _WIN32 //Built-in preprocessor macro for MSVC, MinGW (also for 64 bit)
  #include <Windows/time/GetTimeCount.hpp>
#endif
namespace OperatingSystem
{
#ifdef _WIN32 //Built-in preprocessor macro for MSVC, MinGW (also for 64 bit)
  //TODO: all code into #include <Windows/time/GetTimeCount.hpp>
  inline DWORD GetTimeCountInMilliSeconds(){
    return Windows::GetTimeCountInMilliSeconds(); }
  inline bool GetTimeCountInSeconds(//LARGE_INTEGER *lpPerformanceCount
    long double & TimeCountInSeconds )
  {
    return Windows::GetTimeCountInSeconds(TimeCountInSeconds);
  }
#else
    inline DWORD GetTimeCountInMilliSeconds(){
      return Linux::GetTimeCountInMilliSeconds(); }
    inline bool GetTimeCountInSeconds(long double & TimeCountInSeconds)
      { return Linux::GetTimeCountInSeconds(TimeCountInSeconds); }
#endif
}//namespace OperatingSystem

#endif //#ifndef GETTICKCOUNT_HPP_
