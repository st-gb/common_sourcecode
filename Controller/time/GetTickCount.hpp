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

#ifdef _WIN32 //Built-in preprocessor macro for MSVC, MinGW (also for 64 bit)
  #include <windows.h> // GetTickCount()
  #include <stdint.h> // uint64_t
  #include <preprocessor_macros/logging_preprocessor_macros.h>
  #include <iomanip> //std::setprecision(...)

  bool GetTimeCountInNanoSeconds(//LARGE_INTEGER *lpPerformanceCount
    uint64_t & TimeCountInNanoSeconds )
  {
    LARGE_INTEGER PerformanceCounterValueInCounts;
    //http://msdn.microsoft.com/en-us/library/ms644904
    if( QueryPerformanceCounter(
        & PerformanceCounterValueInCounts )
      )
    {
      DEBUGN( FULL_FUNC_NAME << "--PerformanceCounterValueInCounts:"
        << PerformanceCounterValueInCounts.QuadPart )
      LARGE_INTEGER FrequencyInCountsPerSecond;
      //http://msdn.microsoft.com/en-us/library/ms644905
      if( ! QueryPerformanceFrequency(
          & FrequencyInCountsPerSecond )
        )
        return false;
      DEBUGN( FULL_FUNC_NAME << "--FrequencyInCountsPerSecond:"
        << FrequencyInCountsPerSecond.QuadPart )
      double InS = (double) PerformanceCounterValueInCounts.QuadPart /
        (double) FrequencyInCountsPerSecond.QuadPart;
      DEBUGN( FULL_FUNC_NAME <<
        // http://www.cplusplus.com/reference/iostream/manipulators/scientific/
        std::fixed
        //http://www.cplusplus.com/reference/iostream/manipulators/setprecision/
        << std::setprecision(12) << "--Seconds:" << InS )
      double InNS = InS
        //to nanoseconds
        * 1000000.0f;
      TimeCountInNanoSeconds = InNS;
//      g_logger.m_p_std_ofstream->setf(std::ios_base::fixed);
      DEBUGN( std::fixed << std::setprecision(12) << FULL_FUNC_NAME
        // http://www.cplusplus.com/reference/iostream/manipulators/scientific/
        //http://www.cplusplus.com/reference/iostream/manipulators/setprecision/
         << "--nanoSeconds:" << InNS )
    }
    return false;
  }
#else
  #include <Linux/time/GetTickCount.hpp>
#endif

#endif //#ifndef GETTICKCOUNT_HPP_
