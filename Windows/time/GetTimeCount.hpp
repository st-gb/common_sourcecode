#pragma once

#include <windows.h> // GetTickCount()
#include <stdint.h> // uint64_t
#include <preprocessor_macros/logging_preprocessor_macros.h>
#include <iomanip> //std::setprecision(...)

namespace Windows
{
  inline bool GetTimeCountInSeconds(//LARGE_INTEGER *lpPerformanceCount
    long double & TimeCountInSeconds )
  {
    LARGE_INTEGER PerformanceCounterValueInCounts;
    //http://msdn.microsoft.com/en-us/library/ms644904
    if( ::QueryPerformanceCounter(
        & PerformanceCounterValueInCounts )
      )
    {
//      DEBUGN( FULL_FUNC_NAME << "--PerformanceCounterValueInCounts:"
//        << PerformanceCounterValueInCounts.QuadPart )
      LARGE_INTEGER FrequencyInCountsPerSecond;
      //http://msdn.microsoft.com/en-us/library/ms644905
      //http://msdn.microsoft.com/en-us/library/windows/desktop/ms644905%28v=vs.85%29.aspx:
      //"Not related to CPU frequency in general
      //The high frequency counter need not be tied to the CPU frequency at
      //all. It will only resemble the CPU frequency is the system actually
      //uses the TSC (TimeStampCounter) underneath. As the TSC is generally
      //unreliable on multi-core systems it tends not to be used. When the TSC
      //is not used the ACPI Power Management Timer (pmtimer) may be used.
      //You can tell if your system uses the ACPI PMT by checking if
      //QueryPerformanceFrequency returns the signature value of 3,579,545
      //(ie 3.57MHz). If you see a value around 1.19Mhz then your system is
      //using the old 8245 PIT chip. Otherwise you should see a value
      //approximately that of your CPU frequency (modulo any speed throttling
      //or power-management that might be in effect.)
      //If you have a newer system with an invariant TSC (ie constant frequency
      //TSC) then that is the frequency that will be returned (if Windows uses
      //it). Again this is not necessarily the CPU frequency.
      if( ! ::QueryPerformanceFrequency(
          & FrequencyInCountsPerSecond )
        )
        return false;
//      DEBUGN( FULL_FUNC_NAME << "--FrequencyInCountsPerSecond:"
//        << FrequencyInCountsPerSecond.QuadPart )
      TimeCountInSeconds = (double) PerformanceCounterValueInCounts.QuadPart /
        (double) FrequencyInCountsPerSecond.QuadPart;
      return true;
//      double FrequencyInCountsPerNanoSecond =
//        (double) FrequencyInCountsPerSecond.QuadPart / 1000000000.0f;
//      DEBUGN( FULL_FUNC_NAME <<
//        // http://www.cplusplus.com/reference/iostream/manipulators/scientific/
//        std::fixed
//        //http://www.cplusplus.com/reference/iostream/manipulators/setprecision/
//        << std::setprecision(12) << "--Seconds:" << InS )
//      g_logger.m_p_std_ofstream->setf(std::ios_base::fixed);
//      DEBUGN( std::fixed << std::setprecision(12) << FULL_FUNC_NAME
//        // http://www.cplusplus.com/reference/iostream/manipulators/scientific/
//        //http://www.cplusplus.com/reference/iostream/manipulators/setprecision/
//         << "--nanoSeconds:" << InNS )
    }
    return false;
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
    long double & TimeCountInNanoSeconds )
  {
    bool b = GetTimeCountInSeconds(TimeCountInNanoSeconds);
    if( b )
      TimeCountInNanoSeconds *=
        //to nanoseconds
        //http://en.wikipedia.org/wiki/Nanoseconds:
        //"A nanosecond (ns) is one billionth of a second (10−9 "
        1000000000.0f;
    return b;
  }
}
