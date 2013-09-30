/*
 * GetTickCount.hpp
 *
 *  Created on: Sep 15, 2010
 *      Author: Stefan
 */

//#ifndef GETTICKCOUNT_HPP_
//#define GETTICKCOUNT_HPP_

#ifdef _DEBUG
  #include <preprocessor_macros/logging_preprocessor_macros.h> //DEBUGN(...)
#else
  #ifndef DEBUGN
    #define DEBUGN(...) /* ->empty*/
  #endif
#endif //#ifdef _DEBUG

#include <time.h> //clock_gettime(...)
  #include <sys/time.h> // gettimeofday(...)
#include <inttypes.h> //uint64_t
//  #include <windef.h> //DWORD

  typedef unsigned long DWORD ;

//  inline bool GetTimeCountInNanoSeconds(long double & TimeCountInNanoSeconds)
//  {
//    DEBUGN(FULL_FUNC_NAME << " begin")
//    //Static:don't create on stack each time (global variable with local scope)
////    static DWORD dwReturnValue ;
//    static timeval timevalCurrentTime ;
//    //TODO
//    //from http://en.wikipedia.org/wiki/System_time#Operating_systems:
////    struct timeval * restrict tp;
////    void *restrict tzp ;
////    gettimeofday(tp, void *restrict tzp);
//    //from http://www.gamedev.net/community/forums/topic.asp?topic_id=437062:
//    gettimeofday(
//      //http://www.gamedev.net/community/forums/topic.asp?topic_id=524616:
//      //Problem: when the system time is changed, the "tick count" is wrong.
//      & timevalCurrentTime,0);
//    //from http://www.gamedev.net/community/forums/topic.asp?topic_id=437062:
////    timeval ts;
////    gettimeofday(&ts,0);
////    lGetTickCount = (INT64)(ts.tv_sec * 1000 + (ts.tv_usec / 1000));
//    DEBUGN("inline DWORD GetTickCount() end")
//    TimeCountInNanoSeconds =
//      //seconds to milliseconds
//      timevalCurrentTime.tv_sec * 1000000 +
//      //Microseconds to nanoseconds
//      timevalCurrentTime.tv_usec * 1000;
//  }

namespace Linux
{
  //see http://www.opengroup.org/onlinepubs/9699919799/functions/gettimeofday.html:
  // "Applications should use the clock_gettime() function instead of the
  //  obsolescent gettimeofday() function."
  inline bool GetTimeCountInNanoSeconds(//long double
      uint64_t & TimeCountInNanoSeconds)
  {
    //from http://linux.die.net/man/3/clock_gettime:
    //CLOCK_REALTIME: System-wide realtime clock. Setting this clock requires
    // appropriate privileges.
    //CLOCK_MONOTONIC: Clock that cannot be set and represents monotonic time
    // since some unspecified starting point.
    struct timespec tp;
    //Link to "librt" for "clock_gettime"
    int ret = clock_gettime(CLOCK_MONOTONIC //clockid_t clock_id
      , & tp //struct timespec *tp
      );
    TimeCountInNanoSeconds = tp.tv_sec * 1000000000 + tp.tv_nsec;
    return ret == 0;
  }

  inline bool GetTimeCountInSeconds(long double & TimeCountInSeconds)
  {
//    static uint64_t ui64TimeCountInSeconds;
//    int ret = GetTimeCountInNanoSeconds(ui64TimeCountInSeconds);

    //from http://linux.die.net/man/3/clock_gettime:
    //CLOCK_REALTIME: System-wide realtime clock. Setting this clock requires
    // appropriate privileges.
    //CLOCK_MONOTONIC: Clock that cannot be set and represents monotonic time
    // since some unspecified starting point.
    struct timespec tp;
    //Link to "librt" for "clock_gettime"
    int ret = clock_gettime(CLOCK_MONOTONIC //clockid_t clock_id
      , & tp //struct timespec *tp
      );
    TimeCountInSeconds = tp.tv_sec + (double) tp.tv_nsec / 1000000000.0;
    return ret;
  }

  inline DWORD GetTickCount()
  {
//    DEBUGN("inline DWORD GetTickCount() begin")
    //Static:don't create on stack each time (global variable with local scope)
//    static DWORD dwReturnValue ;
    static timeval timevalCurrentTime ;
    //TODO
    //from http://en.wikipedia.org/wiki/System_time#Operating_systems:
    //see http://www.opengroup.org/onlinepubs/9699919799/functions/gettimeofday.html:
    // "Applications should use the clock_gettime() function instead of the
    //  obsolescent gettimeofday() function."
//    struct timeval * restrict tp;
//    void *restrict tzp ;
//    gettimeofday(tp, void *restrict tzp);
    //from http://www.gamedev.net/community/forums/topic.asp?topic_id=437062:
    gettimeofday(
      //http://www.gamedev.net/community/forums/topic.asp?topic_id=524616:
      //Problem: when the system time is changed, the "tick count" is wrong.
      & timevalCurrentTime,0);
    //from http://www.gamedev.net/community/forums/topic.asp?topic_id=437062:
//    timeval ts;
//    gettimeofday(&ts,0);
//    lGetTickCount = (INT64)(ts.tv_sec * 1000 + (ts.tv_usec / 1000));
//    DEBUGN("inline DWORD GetTickCount() end")
    return
      //seconds to milliseconds
      timevalCurrentTime.tv_sec * 1000 +
      //Microseconds to milliseconds
      timevalCurrentTime.tv_usec / 1000 ;

//    http://www.tutorials.de/c-c/239813-gnu-c-gettickcount-unter-linux.html
//    #include <sys/sysinfo.h>
//    long getTickCount() // Zeit seit dem Booten in Sekunden
//    {
//     struct sysinfo si;
//     if(sysinfo(&si) == 0) return si.uptime;
//     else return -1L;
//    }
  }
  inline DWORD GetTimeCountInMilliSeconds(){ return GetTickCount(); }
} //namespace Linux
//#endif /* GETTICKCOUNT_HPP_ */
