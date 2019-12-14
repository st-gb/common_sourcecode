#pragma once

#include <windows.h> // GetTickCount()
#include <stdint.h> // uint64_t
#include <preprocessor_macros/logging_preprocessor_macros.h>
#include <iomanip> //std::setprecision(...)
#include "GetTimeCount.h"

#ifdef __cplusplus
namespace Windows_API
{
#endif //#ifdef __cplusplus
  inline bool GetTimeCountInSeconds(long double & timeCountInSeconds)
  {
    timeCountInSeconds = ::GetTimeCountInSeconds();
	if( timeCountInSeconds > 0.0 )
		return 1;
	return 0;
  }
  
  inline DWORD GetTimeCountInMilliSeconds()
  {
    long double TimeCountInMilliSeconds;
    bool b = GetTimeCountInSeconds(TimeCountInMilliSeconds);
    if( b )
	{
      TimeCountInMilliSeconds *=
        /// to milliseconds : 1 s = 1000 ms
        1000.0f;
		return TimeCountInMilliSeconds;
	}
	return 0;	
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
#ifdef __cplusplus
}
#endif //#ifdef __cplusplus
