#pragma once

#include <windows.h> // GetTickCount()
#include <stdint.h> // uint64_t
#include <preprocessor_macros/logging_preprocessor_macros.h>
#include <iomanip> //std::setprecision(...)
#include "GetTimeCount.h"

#ifdef __cplusplus
namespace Windows_API
{
  inline GetTimeCountInSeconds(long double & timeCountInSeconds)
  {
    timeCountInSeconds = ::GetTimeCountInSeconds();
  }
  
  inline DWORD GetTimeCountInMilliSeconds()
  {
    long double TimeCountInMilliSeconds;
    bool b = GetTimeCountInSeconds(TimeCountInMilliSeconds);
    if( b )
      TimeCountInMilliSeconds *=
        //to microseconds : 1 s = 1000 ms 
        1000.0f;
    return TimeCountInMilliSeconds;
  }

  /** get time in 10^(-9) seconds */
  inline bool GetTimeCountInNanoSeconds(//LARGE_INTEGER *lpPerformanceCount
    /*long double */ TimeCountInNanosec_type & TimeCountInNanoSeconds )
  {
    long double TimeCountInSeconds;
    bool b = GetTimeCountInSeconds(TimeCountInSeconds);
    if( b )
      TimeCountInNanoSeconds = (TimeCountInNanosec_type) (TimeCountInSeconds *
        //to nanoseconds
        //http://en.wikipedia.org/wiki/Nanoseconds:
        //"A nanosecond (ns) is one billionth of a second (10−9 "
        1000000000.0f);
    return b;
  }
}
